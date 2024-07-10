#ifndef OS_H
#define OS_H

#include "base.h"

MenuItem* Method::get_os_ptr(){
    MenuItem* os_ptr = new MenuItem;
    os_ptr->name = "os";
    os_ptr->submenu = {
        {"os +", {
            {"alpine +", {
                {"release#cat /etc/os-release#"},
                {"apk official doc site#https://wiki.alpinelinux.org/wiki/Main_Page#"},
                {"apk info +", {{"show all installed apk#apk info#"},
                                {"show all installed apk with 1line desc#apk -vv info#"},
                                {"show detailed info of certain apk#apk info -a ${apk}#"}}},
                {"apk list +#", {{"list all apk according to package indices (APKINDEX.tar.gz)#apk list#"}}},
                {"print alpine runtime arch#apk --print-arch#"},
                {"show graphviz code for apk dependencies#apk dot ${apk}#"},
                {"openrc +", {{"offical git repo doc#https://github.com/OpenRC/openrc#"},
                              {"alpine openrc apk brief doc#https://docs.alpinelinux.org/user-handbook/0.1a/Working/openrc.html#"},
                              {"install openrc for alpine#apk add openrc#"},
                              {"#rc-service#"}}}},
            },
            {"centos +", {
                {"release#cat /etc/os-release#"},
                {"pkg +",{{"show info about a pkg (arch, version, install or not, size...)#yum info ${package_name}#"},
                          {"show version of a pkg#rpm -q ${package_name}#"}}}}},
            {"ubuntu +", {{"release#cat /etc/os-release#"}}},
            {"windows +", {{"notepad +", {{"undo last action#ctrl+z#"},
                                          {"redo last action#ctrl+y#"}}}}}},
        },
    };
    return os_ptr;
}

#endif
