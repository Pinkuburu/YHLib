#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
        set("short",HIW "【名人堂】大厅" NOR);
	set("long", @LONG
这是【终极地狱】的名人堂大厅，你可以看见在大厅的尽头有一
扇不知由什么名贵木料制成地大门(men)。
LONG
	);

	set("exits", ([ 
                "down"  : "/d/city/wfoxd",
                "up"    :__DIR__ "thirdroom",
                "enter" :__DIR__ "mingren",
        ]));

        set("item_desc", ([
                "men" : HIY "这是由名贵地婆娑木制成的大门，它看上去十分华丽。\n" NOR,
        ]));

	set ("no_fight",1);
        create_door("enter", "大门", "out", DOOR_CLOSED);
     	setup();
        replace_program(ROOM);
}
