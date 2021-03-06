// File(/data/room/spooks/yingke.c) of spooks's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "时空隧道迎客厅");
	set ("long", @LONG
这里是时空隧道的主人剑使迎接八方来客的地方。大凡客人来拜
见剑使，少不得在这里寒暄叙话，了尽仰慕之情。东面通往一个茶室，
是主人陪同客人品尝天下名茶之处。 
LONG );

	set("exits", ([
		"north"  : __DIR__"yishiting",
                "south"  : __DIR__"zoudao",
                "east"   : __DIR__"chashi",
	]));

        create_door("east", "木门", "west", DOOR_CLOSED);

        set("objects", ([
                "/d/room/roomnpc/yahuan" : 2,
        ]));

        set("no_sleep_room", 1);
        setup();

        set("room_owner", "剑使");
        set("room_name", "时空隧道");
        set("room_id", "suidao");
        set("room_owner_id", "spooks");
        set("room_position", "青石官道");
}
