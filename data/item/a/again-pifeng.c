// ITEM Made by player(�ǻ�:again) /data/item/a/again-pifeng.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Mon Aug  5 00:28:00 2002
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;32m����[2;37;0m", ({ "pifeng" }));
	set_weight(2400);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[2;37;0m[1;31m���޳�[2;37;0m���ƶ��ɵ�һ��ս�¡�
ս��Ե�Ͽ���һ��С�֣��ǻ�(again)
");
	set("value", 2000000);
	set("point", 145);
	set("material", "stone");
	set("wear_msg", "[33m$N[33mװ��[1;32m����[2;37;0m[33m��[2;37;0m\n");
	set("remove_msg", "[33m$N[33m������[1;32m����[2;37;0m[33m��[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
