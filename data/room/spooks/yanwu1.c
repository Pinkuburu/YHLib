// File(/data/room/spooks/yanwu1.c) of spooks's room
// Create by LUBAN written by Doing Lu

     inherit PRIVATE_ROOM;

void create()
{
        set("short", "时空隧道演武厅");
	set ("long", @LONG
这是时空隧道的演武厅，有时有些江湖朋友来会，想一试身手，
就在这里比武较量。 
LONG );

	set("exits", ([
                "west" : __DIR__"yishiting",
	]));

        set("objects", ([
                "/clone/weapon/zhubang" : 1,
                "/clone/weapon/zhujian" : 1,
                "/clone/weapon/mudao"   : 1,
        ]));

        set("no_sleep_room", 1);
        setup();

        set("room_owner", "剑使");
        set("room_name", "时空隧道");
        set("room_id", "suidao");
        set("room_owner_id", "spooks");
        set("room_position", "青石官道");
}
