// File(/data/room/wulaoer/yingke.c) of wulaoer's room
// Create by LUBAN written by Doing Lu

#include <room.h>

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "泥巴城堡迎客厅");
	set ("long", @LONG
这里是泥巴城堡的主人乌老二迎接八方来客的地方。大凡客人来
拜见乌老二，少不得在这里寒暄叙话，了尽仰慕之情。东面通往一个
茶室，是主人陪同客人品尝天下名茶之处。 
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

        set("room_owner", "乌老二");
        set("room_name", "泥巴城堡");
        set("room_id", "mud");
        set("room_owner_id", "wulaoer");
        set("room_position", "青石官道");
}
