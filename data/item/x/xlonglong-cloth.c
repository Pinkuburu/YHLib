// ITEM Made by player(С����:xlonglong) /data/item/x/xlonglong-cloth.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Oct 11 21:16:34 2002
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;37m����ս��[2;37;0m", ({ "cloth" }));
	set_weight(2400);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[2;37;0m[1;31m���޳�[2;37;0m���ƶ��ɵ�һ��ս�¡�
ս��Ե�Ͽ���һ��С�֣�С����(xlonglong)
");
	set("value", 2000000);
	set("point", 136);
	set("material", "stone");
	set("wear_msg", "[33m$N[33mװ��[1;37m����ս��[2;37;0m[33m��[2;37;0m\n");
	set("remove_msg", "[33m$N[33m������[1;37m����ս��[2;37;0m[33m��[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
