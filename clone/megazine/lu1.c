#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIG "【幽风谷小路】" HIY);
        set("long", @LONG                     
四周的悬崖又向你靠拢了一点,苍鹰叫声已经听不清楚了.
由于你已经走入浓雾笼罩的树林，你只能磕磕碰碰的向前走去。
LONG);
         set("exits", ([
             "north" : __DIR__"men",
             "south" : __DIR__"lu",
	]));
        set("objects", ([
             "/clone/beast/jinshe.c" : 1,
             //"/d/baituo/npc/fox.c" : 1,

	]));

    setup ();     
	replace_program(ROOM);
}

