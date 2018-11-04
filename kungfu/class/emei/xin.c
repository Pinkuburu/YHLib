#include <ansi.h>
#include "tobebonze.h"
#include "emei.h"

inherit NPC;
inherit F_GUARDER;
inherit F_MASTER;

void create()
{
        set_name("����ʦ̫", ({ "jingxin shitai","jingxin","shitai"}));
        set("long", "����һλ������ҵ��ã����ڸ�£����ü��Ŀ��\n");
        set("gender", "Ů��");
        set("age", 45);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("class", "bonze");

        set("str", 20);
        set("int", 21);
        set("con", 24);
        set("dex", 21);

        set("inquiry",([
                "���"  : (: ask_for_join :),
                "����"  : (: ask_for_join :),
                "����"  : "���ҵ��ӣ����ܻ��ס���������ʦ̫�ɡ�",
        ]));

        set("max_qi", 5000);
        set("max_jing", 3000);
        set("neili", 5000);
        set("max_neili", 5000);
        set("combat_exp", 130000);

        set_skill("force", 180);
        set_skill("emei-xinfa", 180);
        set_skill("linji-zhuang", 150);
        set_skill("dodge", 160);
        set_skill("zhutian-bu", 160);
        set_skill("strike", 160);
        set_skill("sixiang-zhang", 160);
        set_skill("jinding-zhang", 160);
        set_skill("finger", 160);
        set_skill("tiangang-zhi", 160);
        set_skill("hand", 160);
        set_skill("jieshou-jiushi", 160);
        set_skill("parry", 160);
        set_skill("sword", 180);
        set_skill("emei-jian", 180);
        set_skill("blade", 180);
        set_skill("yanxing-dao", 180);
        set_skill("literate", 200);
        set_skill("mahayana", 200);
        set_skill("buddhism", 200);
        set_skill("martial-cognize", 100);

        map_skill("force","emei-xinfa");
        map_skill("finger","tiangang-zhi");
        map_skill("dodge","zhutian-bu");
        map_skill("hand", "jieshou-jiushi");
        map_skill("sword","emei-jian");
        map_skill("strike", "jinding-zhang");
        map_skill("blade", "yanxing-dao");
        map_skill("parry","yanxing-dao");

        prepare_skill("hand", "jieshou-jiushi");
        prepare_skill("finger", "tiangang-zhi");

        set("no_teach", ([
                "linji-zhuang" : "�ټ�ʮ��ׯ�����ʦ�����ʦ̫���Դ��ڡ�",
        ]));

        create_family("������", 4, "����");

        set("coagents", ({
                ([ "id"        : "miejue shitai",
                   "startroom" : "/d/emei/hcahoudian", ]),
        }));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.jie" :),
                (: perform_action, "finger.ling" :),
                (: perform_action, "blade.huan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        setup();
        carry_object("/d/city/obj/gangdao")->wield();
        carry_object("/d/city/obj/cloth.c")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if ((int)ob->query("shen") < 1000)
        {
                command("say " + RANK_D->query_respect(ob) +
                        "����������֮�»����Ĳ�����");
                return;
        }

        if ((int)ob->query_skill("mahayana",1) < 50)
        {
                command("say �������͹�����Ϊ�����������Щ�����ɡ�");
                return;
        }

        command("say �����ӷ����գ����գ��ðɣ��Ҿ��������ˡ�");
        command("say ϣ�������Դȱ�֮�ģ����ǻ�֮����Ŭ�����ƣ��ö�������");
        command("recruit " + ob->query("id"));
}