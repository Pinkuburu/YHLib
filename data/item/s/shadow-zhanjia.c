// ITEM Made by player(������:shadow) /data/item/s/shadow-zhanjia.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Dec 20 16:10:40 2002
#include <ansi.h>
#include <armor.h>

inherit ARMOR;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;36m��֮���[2;37;0m", ({ "zhanjia" }));
	set_weight(1800);
	set("item_make", 1);
	set("unit", "��");
	set("long", "������[2;37;0m[1;31m���޳�[2;37;0m���ƶ��ɵ�һ�Ż��ס�
����Ե�Ͽ���һ��С�֣�������(shadow)
");
	set("value", 2000000);
	set("point", 131);
	set("material", "stone");
	set("wear_msg", "[33m$N[33mװ��[1;36m��֮���[2;37;0m[33m��[2;37;0m\n");
	set("remove_msg", "[33m$N[33m������[1;36m��֮���[2;37;0m[33m��[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/parry", apply_armor() / 15 + 1);

	setup();
}

string long() { return query("long") + item_long(); }
