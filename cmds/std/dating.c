// skills.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob, man, *all;
	mapping skl, lrn, map;
	string *sname, *mapped;
	int sp, dp;
	int i, cost;
        int sklvl;
        int precise;

	seteuid(getuid());

	all = all_inventory(environment(me));
	for (i = 0; i < sizeof(all); i++)
	{
		if (living(all[i]) && ! userp(all[i]) &&
		    all[i]->query("can_speak") &&
		    ! all[i]->query("not_living"))
		{
			man = all[i];
			break;
		}
	}

        if (me->query("family/family_name") != "丐帮")
		return notify_fail("只有乞丐才能打探别人的技能！\n");

	if (! objectp(man))
		return notify_fail("周围没人能帮你去了解别人的技能！\n");

        if ((sklvl = me->query_skill("checking", 1)) < 30)
		return notify_fail("你的打探本领尚未纯熟，无法"
				   "了解别人的技能！\n");

	if (! arg)
		return notify_fail("你要打听谁的技能？\n");

        if (present(arg, environment(me)))
		return notify_fail("你要打听的人就在边上，在这里"
				   "问不大妥当吧？\n");

	ob = find_player(arg);
	if (! ob) ob = find_living(arg);
	if (! ob) return notify_fail("你要打听谁的技能？\n");

	if (ob == me)
		return notify_fail("不至于吧，要别人告诉你自己的技能？\n");

	cost = me->query("max_jing") / (sklvl / 10) - 10;
        if (cost < 40) cost = 30 + random(10);

	if (me->query("jing") <= cost)
		return notify_fail("现在你太累了，无法去打听别人的技能。\n");
        me->receive_damage("jing", cost);

	tell_object(me, HIY "\n你走上前去，小心翼翼地向" + man->name() + HIY
			"打听关于" + ob->name() + HIY "的情况。\n" NOR);

	message("vision", HIY "只见" + me->name() + HIY "陪着笑脸跟" HIY +
			  man->name() + HIY "说着话，好象在打听些什么。\n" NOR, 
		          environment(me), ({ me, man }) );

	sp = me->query_skill("checking") * 10 + 
	     me->query("jing") + man->query("jing");
	dp = ob->query("jing") * 2;

	if (me->query("combat_exp") < ob->query("combat_exp") * 2 / 3)
		return notify_fail(CYN + man->name() + CYN "摇了摇头，说道：这"
                                   + ob->name() + CYN "比你强多了，没事最好别去"
                                   "招惹。\n" NOR);

	if (random(sp) < random(dp))
		return notify_fail(CYN + man->name() + CYN "摇了摇头，说道：这"
                                   "事可不清楚，" + RANK_D->query_respect(me) +
				   CYN "还是去向别人打听一下吧！\n" NOR);
	skl = ob->query_skills();
	if (! sizeof(skl))
	{
		write(WHT + man->name() + WHT "告诉你： " + ob->name() +
		      WHT "目前并没有学会任何技能。\n" NOR);
		return 1;
	}
	write(WHT + man->name() + WHT "告诉你： " + ob->name() + WHT "目"
              "前所学过的技能：\n" NOR);
	sname  = sort_array(keys(skl), (: strcmp :));
	
	map = ob->query_skill_map();
	if (mapp(map)) mapped = values(map);
	if (! mapped) mapped = ({});

	lrn = ob->query_learned();
	if (! mapp(lrn)) lrn = ([]);
	
	i = random(sizeof(skl));

        // 这个是打听到的技能的精确度
        precise = 1000 / sklvl;

	write(sprintf("%s%s%-40s" NOR " - %3d\n", 
		(lrn[sname[i]] >= (skl[sname[i]] + 1) * (skl[sname[i]] + 1)) ? HIM : "",
		(member_array(sname[i], mapped) == -1? "  " : "□"),
		to_chinese(sname[i]) + " (" + sname[i] + ")",
		(skl[sname[i]] + precise / 2) / precise * precise));

	if (me->can_improve_skill("checking"))
		me->improve_skill("checking", random(me->query("int")));
	return 1;
}

int help(object me)
{
	write(@HELP
指令格式 : check|dating [<某人>]

这个指令可以让你打听别人所学过的技能。你也可以指定一个和你
有师徒关系的对象，用 skills|cha 可以查知对方的技能状况。

此命令为丐帮弟子专用，并需学习相应的技能。如果技能不高，那
么打听出来的可能会有一些出入。如果打探目标的武学强过打探者
太多，则打探不出任何消息。

HELP);
    return 1;
}
