inherit PRIVATE_ROOM;

void create()
{
        set("short", "乾坤居演武厅");
	set ("long", @LONG
这是泥巴城堡的演武厅，有时有些江湖朋友来会，想一试身手，
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

        set("room_owner", "纳兰");
        set("room_name", "乾坤居");
        set("room_id", "qiankun");
        set("room_owner_id", "mong");
        set("room_position", "青石大道");
}
