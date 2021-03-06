// team command: with
// modify by rcwiz

#include <ansi.h>

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object ob;
        object* t; // 队伍人员阵列
        object leader; // 领队
        int tn; // 队伍人数
        
	if (! arg ||
            ! (ob = present(arg, environment(me))) ||
	    ! living(ob) ||
	    ! ob->is_character() ||
	    ob == me)
		return notify_fail("你想和谁成为伙伴？\n");

	if (! pointerp(me->query_team()) || me->is_team_leader())
        {             
                if (sizeof(me->query_team()) >= 18)   // 最多可组成十八罗汉阵
                        return notify_fail("你这个队伍里面的人实在是太多"
                                           "了，大家都照顾不过来了。\n");

		if (me == ob->query_temp("pending/team"))
                {
			if (! pointerp(me->query_team()))
                        {
				ob->add_team_member(me);
				message_vision(HIC "$N" HIC "决定加入$n的队伍。\n" NOR, me, ob);

                                // 当某人加入队伍后建立或呼叫队伍守护进程监视队伍状况
                                // 如出现：非领队人员离开领队所在房间、昏迷，死亡、
                                // 断线、或者主动离开队伍等不能保持队伍完整的情况
                                // 则该队员不属于该队伍，将刷新队伍列表，修正整体
                                // 攻防效果和离开队伍人员攻防效果。
                                remove_call_out("team_tray");                              
                                leader = ob;
                                t = leader->query_team();
                                tn = sizeof(t);
                                // 必须传递参数为tn - 1，因为呼叫守护进程后要等到刷新的时候才更新
                                // 该队员加入后自身和整体攻防效果
                                call_out("team_tray", 1, leader, t, tn - 1); // 刷新队伍守护进程
			} else
                        {
				me->add_team_member(ob);
				message_vision(HIC "$N" HIC "决定让$n加入队伍。\n" NOR, me, ob);

                                // 当某人加入队伍后建立队伍守护进程监视队伍状况
                                // 如出现：非领队人员离开领队所在房间、昏迷，死亡、
                                // 断线、或者主动离开队伍等不能保持队伍完整的情况
                                // 则该队员不属于该队伍，将刷新队伍列表，修正整体
                                // 攻防效果和离开队伍人员攻防效果。
                                leader = me;
                                remove_call_out("team_tray");
                                t = leader->query_team();
                                tn = sizeof(t);
                                // 必须传递参数为tn - 1，因为呼叫守护进程后要等到刷新的时候才更新
                                // 该队员加入后自身和整体攻防效果
                                call_out("team_tray", 1, leader, t, tn - 1); // 刷新队伍守护进程

			}
			ob->delete_temp("pending/team");
			return 1;
		} else
                {
			message_vision(HIM "$N" HIM "邀请$n" HIM "加入$P的队伍。\n" NOR, me, ob);
			tell_object(ob, NOR + YEL "如果你愿意加入，请用 team with " +
                                    me->query("id") + "。\n" NOR);
			me->set_temp("pending/team", ob);
			return 1;
		}
	} else
		return notify_fail("只有队伍领袖可以邀请别人加入。\n");
}

// 队伍守护进程
// 每次呼叫则都刷新整体攻防效果和人员列表
void team_tray(object leader, object* t, int tn)
{
       int i, flag, j, n_ran;
       object tob, target;

       // 进入常规检查（检查队伍状况）
       // 首先检查领队状况（是否仍然存在）
       if ( ! objectp(leader) || ! interactive(leader) || ! living(leader) )
       {                
	    message("team", HIR "【队伍会话】：领队死亡、晕倒或者离线，队伍解"
                            "散！\n" NOR, t);
               
            if (objectp(leader))
            {
                  leader->dismiss_team();
                  flag = 0;
            }
            else 
                  flag = 1;
            
            // 修正整体攻防效果
            for (i = flag; i < tn; i++)
            {
                   if (objectp(t[i]) && t[i]->query_temp("add_power/team"))
                   {                   
                       t[i]->add_temp("apply/attack", -(tn * 16));
                       t[i]->add_temp("apply/armor", -(tn * 18));
	               t[i]->add_temp("apply/parry", -(tn * 10));
	               t[i]->add_temp("apply/dodge", -(tn * 8));
                       t[i]->delete_temp("add_power/team");
                       t[i]->dismiss_team();
                   }
                 
            }
            return;
       }

       // 例行检测队伍完整性（是否已经解散）
       if (! sizeof(leader->query_team())) // 队伍已解散，将进行整体修正
       {
            for (i = 0; i < tn; i++)
            {
                   if (objectp(t[i]) && t[i]->query_temp("add_power/team"))
                   {                   
                       t[i]->add_temp("apply/attack", -(tn * 16));
                       t[i]->add_temp("apply/armor", -(tn * 18));
	               t[i]->add_temp("apply/parry", -(tn * 10));
	               t[i]->add_temp("apply/dodge", -(tn * 8));
                       t[i]->delete_temp("add_power/team");
                   }
                 
            }
            return;
        }
             
       // 然后检查非领队人员是否影响队伍完整性状况
       for (i = 1; i < tn; i ++)
       {
            if (! objectp(t[i]))continue; // 该队员离线

            if (  ! pointerp(t[i]->query_team()) // 该队员已经离开队伍
               || environment(leader) != environment(t[i]) // 该队员和领队不在同一房间               
               || ! living(t[i]) ) // 该队员昏迷或者死亡
            {   
                  // 如果是队员强迫其离队，只删除其个人攻防效果
                  // 其他队员的效果通过后面刷新来完成
                  if (  pointerp(t[i]->query_team()) 
                     && ! t[i]->is_team_leader())
                  {
                            t[i]->dismiss_team();
                            t[i]->add_temp("apply/attack", -(tn * 16));
                            t[i]->add_temp("apply/armor", -(tn * 18));
	                    t[i]->add_temp("apply/parry", -(tn * 10));
	                    t[i]->add_temp("apply/dodge", -(tn * 8));
                            t[i]->delete_temp("add_power/team");
                  }
                  else // 不是队员同样因该删除其攻防效果
                  {
                            t[i]->add_temp("apply/attack", -(tn * 16));
                            t[i]->add_temp("apply/armor", -(tn * 18));
	                    t[i]->add_temp("apply/parry", -(tn * 10));
	                    t[i]->add_temp("apply/dodge", -(tn * 8));
                            t[i]->delete_temp("add_power/team");
                  }
             }

      } // 检查非领队人员完毕

      // 刷新整个队伍！为什么要刷新？几个检查不是已经够了吗？
      // 不，因为中途还有可能随时加入新的队员，必须刷新！
      // 而且其他异常情况需要通过刷新来修正

      // 先删除整体攻防效果      
      for (i = 0; i < tn; i++)
      {                        
             if (objectp(t[i]) && t[i]->query_temp("add_power/team"))
             {                   
                    t[i]->add_temp("apply/attack", -(tn * 16));
                    t[i]->add_temp("apply/armor", -(tn * 18));
                    t[i]->add_temp("apply/parry", -(tn * 10));
	            t[i]->add_temp("apply/dodge", -(tn * 8));
                    t[i]->delete_temp("add_power/team");
              }                 
       }

      // 读取新的队员列表，必须读取一次，可能有新队员加入
      t = leader->query_team();
      t -= ({ 0 });
      tn = sizeof(t); // 这个tn包含了无效和有效物件

      // 修正离线或昏迷死亡人员，因为这些情况其不再是一个物件
      // 如果直接引用会导致出错，而且更严重的是错误不会有提示
      // 其导致队伍守护进程终止，所以必须加上 objectp(ob)加以
      // 判断，如果是物件才能直接引用。
      // 通过这个循环来过滤掉队伍阵列中无效的物件（人员）
      j = 0;
      for (i = 0; i < tn; i++)
      {
              if (! objectp(t[i]))continue;
              j += 1;

      }

      tn = j;
 
      // 如果只剩领队一人的时候队伍解散
      // 必须把这个放在刷新的时候调用，因为如果放在最前面的话
      // 当第一次组队的时候系统首先认为队伍中只有领队一人，然后
      // 才让其他人加入。所以放在前面就会导致永远无法组建队伍

      if (tn <= 1)leader->dismiss_team();

      // 队伍解散后本次不再做修正，留待下次调用队伍守护进程的时候修正

      // 刷新整体攻防效果
      for (i = 0; i < tn; i++)
      {        
               if (! objectp(t[i]))continue;
               t[i]->add_temp("apply/attack", tn * 16);
               t[i]->add_temp("apply/armor", tn * 18);
               t[i]->add_temp("apply/parry", tn * 10);
	       t[i]->add_temp("apply/dodge", tn * 8);
               t[i]->set_temp("add_power/team", 1);
         
      } // 刷新整体攻防效果完毕


  /*  
      ///////////////////////////////////////////////////////////////////////////////////////
      // 每呼叫一次队伍守护进程便进行一次判断
      // 该判断为增加队伍的整体特殊攻击效果
      // 比如随机busy，偷袭、以及消耗对方的精力（大于四人）等。
      // 如果为阵法各种效果还会加强，并且有更多的攻击效果和防御效果
      n_ran = 0;
      if (tn > 1) // 保证队伍没有解散才会有特殊效果
      {    
           // 提取随机busy参数
           switch (tn) // 这个随机busy参数为普通队伍（非阵法）的。阵法的随机busy参数将在后面修正。
           {     // 由于该判断是一秒呼叫一次，所以必须调低几率
                 case 18 : n_ran = 30;  break;
                 case 17 : n_ran = 35;  break;
                 case 16 : n_ran = 45;  break;
                 case 15 : n_ran = 61;  break;
                 case 14 : n_ran = 81;  break;
                 case 13 : n_ran = 103; break;
                 case 12 : n_ran = 130; break;
                 case 11 : n_ran = 160; break;
                 case 10 : n_ran = 195; break;
                 case 9  : n_ran = 235; break;
                 case 8  : n_ran = 283; break;
                 case 7  : n_ran = 338; break;
                 case 6  : n_ran = 350; break;
                 case 5  : n_ran = 370; break;
                 case 4  : n_ran = 392; break;
                 case 3  : n_ran = 398; break;
                 default : n_ran = 2; break;
           } // 提取随机busy参数完毕
      
           // 阵法的随机busy参数将在这里修正
           //...........................
           //...........................
 
          // 随机busy效果开始执行
          // 首先判断队伍是否在群体战斗，先判断领队
          if (objectp(tob)target = tob->select_opponent();
          if (leader->is_fighting(target))
          {                                 
               tob = t[random(tn)]; // 随机获取一个队员
               // 执行特殊busy效果
               if (tob->is_fighting(target) && random(n_ran) == 1)
               {
                      message_vision(HIW "$n" HIW "只觉$N" HIW "等人越攻越猛，不由得阵脚大乱。\n" NOR,
                                     target, leader);
                      
                      if (! target->is_busy())target->start_busy(random(tn));            

               } // 特殊busy效果执行完毕。

                
          }// 
          
      } // 特殊效果执行完毕

//////////////////////////////////////////////////////////       /////////       /////////    
*/
      // 保持队伍守护进程不停止，每隔一秒呼叫一次
      remove_call_out("team_tray");

      // 这个时候的tn为修正后的人员数量不包括昏迷，死亡，或者离线的人员      
      call_out("team_tray", 1, leader, t, tn);
             
}
