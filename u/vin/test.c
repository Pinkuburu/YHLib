#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
        set_name(HIY "TEST第四代黄金版" NOR, ({ "test" }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", WHT "\n
┏━━━━━━━━━━━━━━━━━━━┓
┃                                      ┃
┃    " HIY "临时工具，穿戴后" HIR "IQ" HIY "将提升一万。" NOR + WHT "    ┃
┃                                      ┃
┃" HIY "setnew" NOR + WHT " ：   设定初始状态。            ┃
┃" HIY "body" NOR + WHT "   ：   状态恢复，潜能增加至上限。┃
┃" HIY "money" NOR + WHT "  ：   得到一两黄金。            ┃
┃" HIY "shen + | -" NOR + WHT "：得到一万正神或是负神。    ┃
┃                                      ┃
┃   " HIR "制作公司：炎黄实业股份开发有限公司" NOR + WHT " ┃
┃  " CYN "（附：代办假文凭，传呼：127—88888）" WHT "┃
┃                                      ┃
┗━━━━━━━━━━━━━━━━━━━┛
\n" NOR);
                set("unit", "具");
                set("material", "cloth");
                set("armor_prop/armor", 1);
                set("armor_prop/int", 10000);
        }
        setup();
}

void init()
{
        add_action("do_full1", "setnew");
        add_action("do_full2", "body");
        add_action("do_full3", "money");
        add_action("do_full4", "shen");
}

int do_full1(string str)
{
      object me = this_player();
      me->set("combat_exp", 500000);
      me->set("gongxian", 10000);
      me->set("weiwang", 10000);
      me->set("score", 10000);
      me->set("mud_age", 10000);
      me->set("max_neili", 2000);
      me->set("max_jingli", 2000);
      me->set_skill("literate", 200);
      me->save();
      tell_object(me, HIC "状态社定完成，如果再次使用此命令，将会恢复至此状态。\n" NOR);
      return 1;
}

int do_full2(string str)
{
        object ob = this_player();
        mapping my;

        if (ob->is_fighting())
                return notify_fail("老兄，你在打架耶。别耍流氓好不好？\n");

        my = ob->query_entire_dbase();
        my["jing"]   = my["eff_jing"]   = my["max_jing"];
        my["jingli"] = my["eff_jingli"] = my["max_jingli"];
        my["qi"]     = my["eff_qi"]     = my["max_qi"];
        my["neili"]  = my["max_neili"];
        my["food"]   = ob->max_food_capacity();
        my["water"]  = ob->max_water_capacity();

        ob->set("potential", ob->query_potential_limit());
        tell_object(ob, HIC "状态已经恢复。\n" NOR);
        return 1;
}

int do_full3(string str)
{
        object ob, me = this_player();

        ob = new("/clone/money/gold");
        ob -> move(me, 1);
        tell_object(me, HIC "你获得了一两黄金。\n" NOR);
        return 1;
}

int do_full4(string arg)
{
      object me = this_player();

      if (! arg || (arg != "+" && arg != "-"))
		return notify_fail("\n你要正神还是负神？\n");

      if (arg == "+")
	      me->add("shen", 10000);
      else
	      me->add("shen", -10000);

      tell_object(me, HIC "神的设定完成。\n" NOR);
      return 1;
}
