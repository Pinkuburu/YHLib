inherit ROOM;

void create()
{
	set("short", "���޷�");
	set("long", @LONG
���޷�������˼���Ǹ�������ס�ĵط���������ʵ���������Ѿ�����
�������������Ӧ�ý����������ġ����Ǵ���Ѿ�ϰ���ˣ����Ǳ㻹��ô
�С�����ס������������ˣ�Ҳ��Щ������ʹ����������·����������Ҳ
ס���������ĸ����������кܶ�ܺõĻ����Ҷ�ϲ����������
����ͷǳ��������ˡ�
LONG);
	set("no_clean_up", 0);
	set("exits", ([
  		"south" : __DIR__"wroad1",
	]));
        set("objects", ([
                "/d/xiangyang/npc/gaoli" : 1,
        ]));
	setup();
	replace_program(ROOM);
}