// peacock.c

#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;
inherit F_NOCLONE;

void create()
{
        if( clonep() )
        {
		set_default_object(__FILE__);
        }

	set_name(HIR "火麒麟" NOR, ({ "huo qilin","qilin" }));
       set_weight(1);
       set("long",HIR  "一只火麒麟，身边火雾弥漫，瑞气千条，背"
                   "后隐隐现出五色毫光。\n" NOR);
	set("gender", "雄性");
	set("age", 2000);
	set("attitude", "peaceful");
        set("rideable", 1);
	setup();
}

void kill_ob(object ob)
{
}

void receive_damage(string type, int amount, object from)
{
        return;
}

void unconcious()
{
        die();
}

void die()
{
        message_vision(HIC "$N" HIC "一抖五色毫光，驾起"
                       "火雾消失不见。\n" NOR, this_object());
        destruct(this_object());
}

void init()
{
        add_action("do_follow", "follow");
        add_action("do_ride", "ride");
        add_action("do_ride", "qi");
}

int do_follow(string arg)
{
        object me;
        
        if (arg != "me")
                return 0;

        me = this_player();
        if (me->query("id") != "wfoxd")
                return 0;

        message_vision("$N跟在$n的后面。\n", this_object(), me);
        set_leader(me);
        return 1;
}

int do_ride(string arg)
{
        object me;

        me = this_player();
        if (me->query("id") != "wfoxd")
                return 0;

        if (! arg || ! id(arg))
                return 0;

        if (me->query_temp("is_riding"))
        {
                write("你现在正骑在" + me->query_temp("is_riding")->name() +
                      "上呢。\n");
                return 1;
        }

        if (move(me))
        {
                message_vision(HIC "$N" HIC "迅速的骑上$n"
                               HIC "，姿势甚是豪放，$n"
                               HIC "一抹五色毫光，现出红云朵朵。\n",
                               me, this_object());
                set_temp("is_rided_by", me);
                me->set_temp("is_riding", this_object());
        } else
        {
                write("你身上带的东西太重了，无法骑上去。\n");
        }
        return 1;
}

int receive_summon(object me)
{
        object env;

        if (objectp(env = environment()) && env == environment(me))
        {
                write(name() + "不就在你身边嘛？不必召唤了。\n");
                return 1;
        }

        if (env)
        {
                message_vision(HIC "$N" HIC "一抖五色毫光，驾起"
                               "火雾消失不见。\n" NOR, this_object());
        }

        move(environment(me));
        message_vision(HIY "天现红云万朵，一时间氤氲遍地，万物俱震，一只$N"
                       HIY "驾五色毫光而来。\n", this_object());
        return 1;
}

int hide_anywhere(object me)
{
        if (me->query("id") != "wfoxd")
                return 0;

        message_vision(HIB "$N" HIB "雄姿一展，驾起五色毫光，"
                       "须臾便了无踪迹。\n", this_object());
        destruct(this_object());
        return 1;
}
