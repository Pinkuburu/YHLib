// File(/data/room/shaqian/dating.c) of shaqian's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "小院大厅");
	set ("long", @LONG
这就是小院主人杀钱迎送客人的地方。正中有些桌椅，侧面是两
扇屏风。东首是主人杀钱的房间，有一扇木门虚掩着。南边是大门，
出去就是院子。 
LONG );

	setup();

	set("exits", ([
                "east"   : __DIR__"woshi",
		"north"  : __DIR__"houyuan",
	]));

        create_door("east", "木门", "west", DOOR_CLOSED);

        set("no_sleep_room", 1);

        set("KEY_DOOR", ([
                "exit" : "south",
                "room" : __DIR__"xiaoyuan",
        ]));
    
        set("room_owner", "杀钱");
        set("room_name", "小院");
        set("room_id", "xyuan");
        set("room_position", "青石官道");
}
