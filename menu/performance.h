#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include "base.h"

MenuItem* Method::get_performance_ptr(){
    MenuItem* performance_ptr = new MenuItem;
    performance_ptr->name = "performance";
    performance_ptr->submenu = {
        {"performance +", {
            {"perf +", {
                {"list +", {{"list all supported events#perf list#"},
                            {"list hardware events#perf list hw#"},
                            {"list PMU (performance monitor unit) events#perf list pmu#"}}},
                {"record +", {{"record PMU event stat of certain process for a period#perf record -g -p ${pid} -- sleep ${time_to_record}#"},
                              {"record PMU event stat of binary executable at certain sampling rate#perf record -F 4000 -g -o perf.data ./out#"}}},
                {"report +", {{"report call-graph for generated perf file with statistics#perf report --stdio -ng#"}}},
                {"script +", {{"generate flamegreph using perf.data output#perf script | ./stackcollapse-perf.pl | ./flamegraph.pl > flame.svg#"}}}}},
            {"top +", {{"setup top display interval#top -d ${interval}#"},
                       {"give a snapshot for all processes of current user#top -bn1 -u $(id -u)#"}}},
            {"memory +", {
                {"free +", {{"show manual#man free#"},
                            {"show [total, used, free, shared, buff/cache, available]#free -h#"},
                            {"show memory info update once in 1 second#watch -n 1 'free -h'#"}}},
                {"detailed meminfo#cat /proc/meminfo#"}}}},
        },
    };
    return performance_ptr;
}

#endif
