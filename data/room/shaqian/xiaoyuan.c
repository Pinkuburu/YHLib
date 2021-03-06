// File(/data/room/shaqian/xiaoyuan.c) of shaqian's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "小院小院");
	set ("long", @LONG
这里是一个四四方方的院子，院墙都是用红砖砌成，不算高，但
是非常清爽利落。院中几棵古木成荫，隐然有一种世外桃源的感觉。
院子外面隐约是青石官道，院子的北面有一扇木门。 
LONG );

        set("room_key", "1 of shaqian");
	setup();

	set("exits", ([
                "out"    : "/d/suzhou/road1",
	]));

        set("outdoors", "suzhou");
        set("no_sleep_room", 1);
        set("valid_startroom", 1);

        set("KEY_DOOR", ([
                "exit" : "north",
                "room" : __DIR__"dating",
        ]));
    
        set("room_owner", "杀钱");
        set("room_name", "小院");
        set("room_OWNER_ID", "shaqian");
        set("room_id", "xyuan");
        set("room_position", "青石官道");
}
