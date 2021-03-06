#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "\n\n                林     间     圣     地" NOR);
        set("long", HIW "\n
这是一片暗绿色的森林，青草铺地，密叶遮天。一阵微风拂过
带来几许醉人的凉意。森林四周一片寂静，仅能听见草丛中昆
虫的低吟以及偶尔传来的几声独角兽的嘶鸣。森林正中有一波
清泉，" HIG "泉水" HIW "(" HIG "fountain" HIW ")极为清"
"澈诱人，一道彩虹架于清泉之上。\n几只独角兽正围绕在泉边嬉戏。
\n" NOR);
        set("item_desc", ([
                "fountain" : HIG "泉水波光粼粼，极为清澈诱人，你"
                             "不禁想捧一口喝喝。\n" NOR,
        ]));
        set("objects", ([
                __DIR__"dujiaoshou" : 1,
        ]));
        set("no_fight", 1);
        set("sleep_room", 1);
        setup();
}

void init()
{
        add_action("drink", "drink");
}

int drink(string arg)
{
        object me = this_player();
        int exp, n, p;

        if (! arg || arg == "")
                return 0;

        if (arg == "fountain")
        {
                if (me->is_busy())
                {
                        return notify_fail("你的动作还没有完成，不能移动。\n");
                        return 1; 
                }

                if (me->query("sys/02.5.1"))
                {
                        message_vision(HIR "\n$N" HIR "双手刚捧起泉水，突然间一阵"
                                       "嘶鸣，被" HIW "獨角獸" HIR "一角顶得飞了出"
                                       "去。\n\n" NOR, me);
                        me->move("/d/city/guangchang");
                        return 1; 
                }

                exp = me->query("combat_exp");

                if (exp >= 300000)
                        n = 50000;
                else
                if (exp >= 200000)
                        n = 30000;
                else
                if (exp >= 100000)
                        n = 10000;
                else
                if (exp >= 50000)
                        n = 5000;
                else
                if (exp >= 10000)
                        n = 3000;
                else
                        n = 0;

                p = n * 2 / 5;

                me->add("combat_exp", n);
                me->add("potential", p);
                me->set("sys/02.5.1", 1);
                message_vision(HIG "\n$N" HIG "双手捧起泉水一饮而下，只觉入口甘甜"
                               "无比，说不出的清欣爽口。\n" NOR, me);
                tell_object(me, HIC "你获得了" + chinese_number(n) +
                                "点经验及" + chinese_number(p) +
                                "点潜能的补偿。\n" NOR);
                return 1;
        }
}
