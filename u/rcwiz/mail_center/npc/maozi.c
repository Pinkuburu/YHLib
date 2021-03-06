
#include <ansi.h>

inherit NPC;

#define SAVE_MAILF "/u/rcwiz/mail_center/to_user_mails/" + user + ".m"

int rebuild_data();
mixed register_mail();

void create()
{
        seteuid(getuid());
        set_name("毛子", ({ "mao zi", "mao", "zi" }) );
        set("title", HIY "炎黄信使" NOR);
        set("nickname", HIW "夺命书生" NOR);
        set("gender", "男性" );
        set("age", 22);
        set("long", "没什么好看的，很丑。\n");

        set("str", 40);
        set("con", 40);
        set("int", 40);
        set("dex", 40);

        set("max_qi", 100000);
        set("max_jing", 100000);
        set("neili", 100000);
        set("max_neili", 100000);
        set("jiali", 400);
        set("shen_type", 0);
        set("attitude", "peaceful");

        set_temp("apply/attack",  200);
        set_temp("apply/defense", 200);

        set("combat_exp", 8000000);

        set_skill("force", 500); 
        set_skill("dodge", 500);
        set_skill("parry", 500);
        set_skill("finger", 500);
        set_skill("martial-cognize", 500); 
        set_skill("yinyang-shiertian", 500); 

        map_skill("force", "yinyang-shiertian");
        map_skill("finger","yinyang-shiertian");
        map_skill("parry", "yinyang-shiertian");
        map_skill("dodge", "yinyang-shiertian");

        set("inquiry", ([
                "修复数据" : (: rebuild_data :),
                "注册"     : (: register_mail :),
        ]));

        setup();

        carry_object("/clone/cloth/cloth")->wear();
        
}

mixed register_mail()
{
        object me = this_player();
        string user, str;

        if (! me->query("register_heromail"))
        {
              user = me->query("id");
              str = "REFUSE={0}";
              write_file(SAVE_MAILF, str, 1);          
              str += "\nSETTINGS={REPLY:0:MSG:0:no_name:0}=SETTING_END";
              str += "\nMAIL_TO_START={WHO_SEND_MAIL:炎黄邮件系统:MAIL_TOPIC:欢迎使用炎";
              str += "黄邮件系统:SEND_TIME:" + ctime(time()) + ":MAIL_IS_NEW:1}";
              str += "\n{MAIL_TEXT:敬爱的" + me->query("name") + ":\n";
              str += "    你好！非常欢迎你使用炎黄邮件系统，请勿在邮件中传发任何";
              str += "淫秽、反动、恐怖、暴力等信息。有问题请及时联系炎黄巫师，希望";
              str += "该邮件系统能给你带来便利，也希望你能够不懈地支持炎黄！";
              str += "\n                   --炎黄英雄史 http://heros-cn.51.net";
              str += "\n}=MAIL_TO_END";
              write_file(SAVE_MAILF, str, 0);
        }
        else
        {
              write("你已经注册过了！\n");
              return 1;
        }

        write("Register OK!\n");
        if (! me->query("register_heromail"))
              write(HIW "你的邮件箱中有一封新邮件！\n" NOR);
        me->set("register_heromail", 1);
  
        return 1;    
}

int rebuild_data()
{
        object me = this_player();        
        string user, str;
        
        user = me->query("id");
        // 注册过才可以修复
        if (! me->query("register_heromail"))
               return notify_fail("毛子说道：“你必须注册先。”\n");

        if (! me->query_temp("want_rebuild"))
        {
               write(HIR "毛子说道：“修复邮件箱将删除掉你邮件箱中所有数据，如果确定要"
                     "修复再来问我一次。”\n" NOR);
               me->set_temp("want_rebuild", 1);

               return 1;
        }
        write("毛子点了点头说道：“好吧，我这就帮你修复，等等……” \n");
                 
        str = "REFUSE={0}";
        write_file(SAVE_MAILF, str, 1);
        str = "\nSETTINGS={REPLY:0:MSG:0:no_name:0}=SETTING_END";
        str += "\nMAIL_TO_START={WHO_SEND_MAIL:炎黄邮件系统:MAIL_TOPIC:欢迎使用炎";
        str += "黄邮件系统:SEND_TIME:" + ctime(time()) + ":MAIL_IS_NEW:1}";
        str += "\n{MAIL_TEXT:敬爱的" + me->query("name") + ":\n";
        str += "    你好！非常欢迎你使用炎黄邮件系统，请勿在邮件中传发任何";
        str += "淫秽、反动、恐怖、暴力等信息。有问题请及时联系炎黄巫师，希望";
        str += "该邮件系统能给你带来便利，也希望你能够不懈地支持炎黄！";
        str += "\n                   --炎黄英雄史 http://heros-cn.51.net";
        str += "\n}=MAIL_TO_END";
        write_file(SAVE_MAILF, str, 0);        
        write("毛子擦了擦头上的汗说道：“好了，已经修复了，放心用吧！\n");
        me->delete_temp("want_rebuild");
       
        return 1;
}      


