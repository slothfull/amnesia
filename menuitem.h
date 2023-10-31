#include <vector>
#include <string>
#include <map>

struct MenuItem{
    std::string name;
    std::vector<MenuItem> submenu;
};

// load data into menu data structure => todo: move the data structure to a standalone file
MenuItem* initdata(){
    // Create the menu structure
    MenuItem *menu_ptr = new MenuItem;;
    menu_ptr->name = "Main Menu";
    menu_ptr->submenu = {
        {"mac +", {{"system integrity protection(SIP) +", {{"check SIP status#csrutil status#test"},
                                                           {"enable SIP#csrutil enable#"},
                                                           {"disable SIP#csrutil disable#"}}},
                   {"desktop icon +", {{"show icon#defaults delete com.apple.finder CreateDesktop; killall Finder#"},
                                       {"hide icon#defaults write com.apple.finder CreateDesktop -bool FALSE; killall Finder#"}}},
                   {"software install permission +", {{"disable install from all source#sudo spctl --master-disable#"},
                                                      {"enable install from all source#sudo spctl --master-enable#"}}},
                   {"show mac battery capacity#ioreg -rn AppleSmartBattery | grep -i capacity#"},
                   {"build mac app by applescript#osacompile -o ${appname.app} ${applescript.scpt}#"}}},
        {"transhell#docker run --rm -it transhell -shell#"},
        {"blog +", {{"twistefatezzz +", {{"edit twistfatezzz blog#"},
                                         {"start twistfatezzz jekyll server#"}}},
                    {"booming melon +", {{"edit melon blog dockerfile#nvim /User/mac/paper/Dockerfile#"},
                                         {"edit melon blog#nvim /Users/mac/paper/blog/#"},
                                         {"start melon jekyll server#"}}}}},
        {"latex +", {{"build texlive pdflatex en#docker run --rm -i -v $PWD:/data latex pdflatex ${en}.tex#"},
                     {"build texlive xelatex zh#docker run --rm -i -v $PWD:/data latex xelatex ${zh}.tex#"}}},
        {"gnu +", {{"gnu tools manuals#https://www.gnu.org/manual/#"}}},
        {"revision control +", {
            {"git +", {{"git init +", {{"*init git repo in current dir#git init#gitinit"},
                                       {"del git repo in current dir#rm -rf .git#"}}},
                       {"git config +", {{"list all config#git config --list#"}, 
                                         {"list system level config#git config --list --system#"}, 
                                         {"*list global level config#git config --list --global#gitconfig"},
                                         {"list local repo level config#git config --list --local#"}, 
                                         {"list config located at file#git config --list --file ${file}#"}}},
                       {"git clone +", {{"get repo by ssh from remote (no user/passwd needed)#git clone git@github.com:${project}.git#"},
                                        {"get repo by https from remote (user/passwd needed)#git clone https://github.com/${project}.git#"}, 
                                        {"get only a specific branch from remote#git clone -b ${branch} git@github.com:${project}.git#"}}},
                       {"git diff +", {{"show diff between wkdir vs staged#git diff#"},
                                       {"show diff between wkdir vs staged with colored text#git diff --color#"}, 
                                       {"show diff between wkdir vs staged with colored word-by-word diff#git diff --color-words#"}, 
                                       {"show diff between staged vs committed#git diff --staged#"}}}, 
                       {"git show +", {{"show code changes made by latest commit#git show HEAD#"}, 
                                       {"show code changes made by the second latest commit#git show HEAD^#"},
                                       {"show code changes made by certain commit#git show ${commitid}#"}}},
                       {"git add +", {{"add certain file's changes in wkdir to staged#git add ${file}#"}, 
                                      {"add changes recursively from cur wkdir to staged(ignore removal)#git add .#"}, 
                                      {"add changes of all wkdir to staged(hg addremove)#git add --all#"}}},
                       {"git rm +", {{"todo#git rm ${file}#"}, 
                                     {"todo#git rm -r $[dir}#"}, 
                                     {"remove file from git tracking cache without really del it#git rm --cached ${file}#"}, 
                                     {"remove dir from git tracking cache without really del it#git rm -r --cached ${dir}#"}}},
                       {"git status +", {{"show modified files in both working dir & staged#git status#"}}},
                       {"git reset +", {{"*unstage a file to wkdir#git reset ${file}#gitreset"},
                                        {"*unstage all files to wkdir#git reset#gitreset"},
                                        {"*reset workdir/index to certain rev#git reset --hard ${revision}#gitreset"},
                                        {"*reset committed to index#git reset --soft ${revision}#gitreset"}}},
                       {"git outgoing: check between local cur branch with remote branch#git fetch && git log origin/${branchname}.. --oneline#"},
                       {"git incoming: check between local cur branch with remote branch#git fetch && git log ..origin/${branchname} --oneline#"},
                       {"git log +", {{"*show commits of a branch#git log ${branch}#gitlog"},
                                      {"*show commits of a branch in format: hash/date/message#git log --graph --pretty=\"%C(yellow) Hash: %h %C(blue)Date: %ad %C(red) Message: %s \" --date=iso ${branch}#gitlog"},
                                      {"*show commits of a branch in format: 1-line,graph,decorate#git log --oneline --graph --decorate ${branch}#gitlog"},
                                      {"*show commits in refs/ of a branch in format: 1-line,graph,decorate#git log --oneline --graph --decorate --all ${branch}#gitlog"},
                                      {"*show commits of a file in cur branch#git log --graph --oneline --decorate --follow ${file}#gitlog"},
                                      {"*show commits of branchB not of branchA#git log ${branchA}..${branchB}#gitlog"}, 
                                      {"show reflog based on all commits#git log --reflog --patch#"},
                                      {"show reflog based on local recent commits#git log --reflog --no-walk --patch#"},
                                      {"*show reflog based on local recent commits#git log --reflog --oneline --no-walk#gitreset"}}},
                       {"git reflog +", {{"*show reflog based on the local changes (more fine-grained than commit)#git reflog#gitreset"}}},
                       {"git annotate +", {{"show annotations: commitid,author,date,lines#git annotate --show-stats ${file}#"}, 
                                           {"git annotate --show-stats -L ${startlineno},${endlineno}"}}},
                       {"git fetch#git fetch#"}, 
                       {"git pull = git fetch + git merge#git pull#"},
                       {"git push +", {{"push commit to remote (the same branch as local)#git push -u origin#"},
                                       {"push commit to certain branch of origin#git push -u origin ${branch}#"},
                                       {"forcibly overwrite remote with local (share the same branch name)#git push -f ${remote} ${branch}#"},
                                       {"forcibly overwrite remote with local (branch name are not different)#git push -f ${remote} ${localbranch}:${remotebranch}#"},
                                       {"delete remote branch#git push ${origin} -d ${branch}#"}}},
                       {"git branch +", {{"*list local branches#git branch --list#gitbranch"},
                                         {"*list remote branches#git branch --list -r#gitbranch"},
                                         {"*list local+remote branches#git branch --list -a#gitbranch"},
                                         {"*list local+remote branches (verbose)#git branch --list -av#gitbranch"},
                                         {"*list local+remote branches (complete)#git branch --list -avv#gitbranch"},
                                         {"*del local branch#git branch -d ${origin}/${branch_to_del}#gitbranch"},
                                         {"*del remote branch#git branch -d -r ${origin}/${branch_to_del}#gitbranch"}}},
                       {"git checkout +", {{"*discard wkdir changes & update wkdir to cur branch#git checkout -f#gitcheckout"},
                                           {"*discard wkdir changes & update wkdir to certain branch#git checkout -f -b ${branch}#gitcheckout"},
                                           {"*change wkdir/index to certain branch & point HEAD at the branch#git checkout ${branch}#gitcheckout"},
                                           {"*create new branch & startup at commit#git checkout -b $(branch} ${commit}#gitcheckout"}, 
                                           {"*revert file1/file2 in wkdir/index to certain commit#git checkout ${commit} -- ${file1} ${file2}...#gitcheckout"}}}, 
                       {"git rebase +", {{"*rebase upstream changes with cur working branch#git rebase ${upstream_branch}#gitrebase"}, 
                                         {"*rebase upstream changes with specified branch#git rebase ${upstream_branch} ${working_branch}#gitrebase"}, 
                                         {"rebase upstream changes with cur working branch in interative mode#git rebase -i ${upstream_branch} ${working_branch}#"}}},
                       {"git remote +", {{"show configured remote name:url for cur repo#git remote -v#"}, 
                                         {"add url as remote of current repo with a name#git remote add ${name_for_remote} ${remote_repo_url}#"}}}}},
            {"mercurial +", {{"hg help +", {{"show available hg format templates#hg help templates#"},
                                            {"show help page for hg subcommand(e.g. hg help diff)#hg help ${subcommand}#"}}},
                             {"hg head +", {{"show all open head in current repo#hg head#"},
                                            {"show all descendant head from start revision#hg head -r ${rev}#"},
                                            {"show all topological head(head without child)#hg head -t#"},
                                            {"show all active head#hg head -a#"},
                                            {"show all closed head#hg head -c#"}}},
                             {"hg diff +", {{"show diff of file(wkdir) with its parent#hg diff ${file}#"},
                                            {"show diff of wkdir with certain revision#hg diff -r ${rev}#"},
                                            {"show diff of file(wkdir) with certain revision#hg diff -r ${rev} ${file}#"},
                                            {"show changes of certain revision#hg diff -c ${rev}#"},
                                            {"show changes of certain file in certain revision#hg diff -c ${rev} ${file}#"}}},
                             {"hg annotate +", {{"show author of each line in certain file#hg annotate -u ${file}#"},
                                                {"show author of each line in certain revision#hg annotate -r ${rev} -u ${file}#"},
                                                {"show author / revision / changeset / lineno of certain revision#hg annotate -u -n -c -l ${file}#"}}},
                             {"hg commit +", {{"commit current changeset#hg commit#"}, 
                                              {"commit current changeset with messages#hg commit -m ${message}#"},
                                              {"commit changes of wkdir to current parent#hg commit --amend#"}}},
                             {"hg revert +", {{"tips for testing temporary changes#revert wkdir to ref changeset, do some tests, hg update -C to fallback#"}, 
                                              {"revert certain file in wkdir to state of certain revision#hg revert -r ${rev} ${file}#"},
                                              {"revert all files in wkdir to state of certain revision#hg revert -r ${rev} --all#"}}},
                             {"hg pull +", {{"pull all incoming changesets to local#hg pull#"}, 
                                            {"pull all incoming changesets till certain revision to local#hg pull -r ${rev}#"}}},
                             {"hg update +", {{"update wkdir or switch revisions#hg update#"},
                                              {"discard changes in wkdir(no backup)#hg update -C#"}}},
                             {"hg strip +", {{"restore stripped changeset using the backup file gernerated by hg#see hg unbundle ${backup} for details#"},
                                             {"remove certain revision#hg strip -r ${rev}#"}, 
                                             {"remove certain revision without backups#hg strip -r ${rev} --no-backup#"}}},
                             {"hg export+", {{"export changes of parent revision to screen#hg export#"},
                                             {"export changes of parent revision to file#hg export > ${file}#"},
                                             {"export changes of certain revision to screen#hg export -r ${rev}#"},
                                             {"export changes of certain revision to file#hg export -r ${rev} > ${file}#"}}},
                             {"hg import +", {{"import diff patch and create commit on working head#hg import ${patch}#"},
                                              {"import diff patch to wkdir without commit#hg import --no-commit ${patch}#"}}},
                             {"hg rebase +", {{"rebase revision(src) to the top of another(dst)#hg rebase -s ${rev_src} -d ${rev_dst}#"},
                                              {"rebase revision(src) to the top of another(dst) with merge tool#hg rebase -s ${rev_src} -d ${rev_dst} --tool=vimdiff#"}}},
                             {"hg backout +", {{"backout(del) latest revision, no merge needed#hg backout -r ${latestrev}#"},
                                               {"backout middle revision, merge needed#hg backout -r ${midrev}#"}}},
                             {"hg status +", {{"show changed files of certain revision#hg status --change ${rev}#"},
                                              {"show changed files of wkdir with certain revision#hg status --rev ${rev}#"}}},
                             {"hg log +", {{"show recent num commits#hg log -l ${num}#"},
                                           {"show commits of revision#hg log -r ${rev}#"},
                                           {"show commits of revision verbosely#hg log -r ${rev} -v#"},
                                           {"show commits of certain maintainer#hg log --user ${usr}#"},
                                           {"show commits of certain maintainer in brief mode#hg log --user ${usr} -q#"},
                                           {"show maintainer list#hg log --template \"{author}\\n\" | sort | uniq#"},
                                           {"show commits of some date#hg log --date ${2022-10-20}#"},
                                           {"show commits of certain file#hg log ${file}#"},
                                           {"show commits graph#hg log -G#"},
                                           {"show brief commits with format#hg log -T \"\\t{date|shortdate}\\t[{rev}]\\t{author|user}\\t{desc}\\n\"#"},
                                           {"show brief commits with format in graph mode#hg log -G -T \"\\t{date|shortdate}\\t[{rev}]\\t{author|user}\\t{desc}\\n\"#"},
                                           {"show commit message & changes#hg log -pr ${rev}#"}}},
                             {"hg cat +", {{"show file content of certain revision#hg cat -r ${rev} ${file}#"}}},
                             {"hg tag +", {{"show help page for hg tag#hg help tag#"},
                                           {"tag a certain revision by create commit#hg tag -r ${rev} ${tagname}#"},
                                           {"remove certain tag by create a commit#hg tag --remove ${tagname}#"}}},
                             {"hg in/out +", {{"show all changeset pending to be pushed#hg outgoing(out)#"},
                                              {"show all changeset pendign to be pulled#hg incoming(in)#"}}}}}}},
        {"ps +"},
        {"pstree +"},
        {"ip +", {{"ip addr +", {{"ip addr show +", {{"show netdev info including ip address#ip addr show ${dev}#"},
                                                     {"..."}}}, 
                                 {"ip addr add +", {{"add ip/subnetmask to dev#ip addr add ${ip/subnetmask} dev ${dev}#"}}},
                                 {"ip addr del +", {{"del ip/subnetmask from dev#ip addr del ${ip/subnetmask} dev ${dev}#"}}}}},
                  {"ip link +", {{"ip link help#ip link help#"},
                                 {"ip link add +", {{"add veth pair#ip link add ${veth} type veth peer name ${veth_p}#"},
                                                    {"add veth pair with netns#ip link add ${veth} netns ${netns} type veth peer ${veth_p} netns ${peer_netns}#"},
                                                    {"add bridge#ip link add name ${bridge} type bridge#"}}},
                                 {"ip link delete +", {{"ip link delete ${bridge} type bridge#"},
                                                       {"..."}}},
                                 {"ip link set +", {{"put veth peer to netns#ip link set ${veth_p} netns ${peer_netns}#"},
                                                    {"remove netdev from its master#ip link set ${dev} nomaster#"},
                                                    {"set bridge up#ip link set dev ${bridge} up#"},
                                                    {"set bridge down#ip link set dev ${bridge} down#"},
                                                    {"set veth up#ip link set ${veth} up#"},
                                                    {"set veth down#ip link set ${veth} down#"},
                                                    {"set veth on bridge#ip link set ${veth} master ${bridge}#"},
                                                    {"set veth off bridge#ip link set ${veth} nomaster#"}}},
                                 {"ip link show +", {{"show all interfaces info#ip link show#"},
                                                     {"show basic netdev info#ip link show ${dev}#"}}},
                                 {"ip [option] link +", {{"show all interfaces in color#ip -c link#"},
                                                         {"show certain interface info#ip -c link show ${dev}#"},
                                                         {"show interface statistics#ip -s link#"},
                                                         {"show certain interface info#ip -s link show ${dev}#"}}}}},
                  {"ip route +", {{"ip route show +", {{"show netdev route info#ip route show dev ${dev}#"}}}}},
                  {"ip neigh +", {{"show all ipv4 arp neighbor entries#ip neigh#"},
                                  {"show ipv4 arp neighbor entries for dev#ip neigh show dev ${dev}#"},
                                  {"add ip <-> mac entry for arptable of dev#ip neigh add ${ip} lladdr ${mac} dev ${dev}#"},
                                  {"del the arp entry of ip for dev#ip neigh del ${ip} dev ${dev}"},
                                  {"replace/add the arp entry of ip to new mac for dev#ip neigh replace ${ip} lladdr ${mac} dev ${dev}#"}}}, 
                  {"ip netns +", {{"*show ip netns subcmd help#ip netns help#"}, 
                                  {"*list netns#ip netns list#"}, 
                                  {"*create netns by name#ip netns add ${netnsname}#"}, 
                                  {"*execute cmd in a netns#ip netns exec ${netnsname} ${cmd}#ipnetns"}}}}},
        {"iptables +", {{"show help pages#iptables --help#"},
                        {"iptables list rules +", {{"*list rules of a table(raw mangle nat filter)#iptables -nvL -t ${table}#iptablenat"}, 
                                                   {"*list rules of a chain#iptables -nvL ${chainname}#dockeriptable"}}}}},
        {"ls series +", {{"ls +", {{"show list of file/dir in human readble format, newest modified the first#ls -lht#"}, 
                                   {"show list of file/dir in human readble format, oldest modified the first#ls -lhtr#"}}},
                         {"lsof +", {{"show manual#man lsof#"},
                                     {"show network files in all addr (use portnum not portname)#sudo lsof -i -P#"}}},
                         {"lsns +", {{"show manual for format system namespace output#man lsns#"}, 
                                     {"list system namespaces#lsns -l#"}}}}},
        {"brctl +", {{"brctl show +", {{"show bridge general info#brctl show#"},
                                       {"show bridge info#brctl show ${bridge}#"},
                                       {"show bridge mac info#brctl showmacs ${bridge}#"},
                                       {"show bridge stp info#brctl showstp ${bridge}#"}}},
                     {"brctl addbr +", {{"add bridge#brctl addbr ${dev}#"}}},
                     {"brctl delbr +", {{"del bridge#brctl delbr ${dev}#"}}},
                     {"brctl addif +", {{"add itf to bridge#brctl addif ${bridge} ${interface}#"}}}}},
        {"bridge +", {{"bridge manual ref#https://man.archlinux.org/man/bridge.8#"}}},
        {"ethtool +", {{"ethtool: query network driver/hardware settings#https://man7.org/linux/man-pages/man8/ethtool.8.html#"},
                       {"show network receive/transmit statistics for nic#ethtool -S ${nic}#"},
                       {"show driver info for nic#ethtool -i ${nic}#"},
                       {"show ring buffer info for nic#ethtool -g ${nic}#"},
                       {"show EEPROM data for nic#ethtool -e ${nic}#"},
                       {"show nic by sight: causing nic related light blinking#ethtool -g ${nic}#"}}},
        {"netstat +", {{"show ip routing tables (ip:numerical)#netstat -rn#"}, 
                       {"show active tcp/udp listening sockets (numerical)#netstat -tu -pnl#"}, 
                       {"show all tcp/udp sockets (numerical)#netstat -tu -pna#"}}},
        {"nsenter +", {{"show manual for nsenter#man nsenter#"}, 
                       {"enter into net namespace of pid, display listening program-sock info#sudo nsenter -t ${pid} -n netstat -pnl#"},
                       {"enter into net namespace of pid, display all program-sock info#sudo nsenter -t ${pid} -n netstat -pna#"}}},
        {"tcpdump +", {{"capture packets, enable ip resolution (live)#tcpdump -i ${dev}#"},
                       {"capture packets, disable ip resolution (live)#tcpdump -n -i ${dev}#"},
                       {"capture packets, disable ip/port resolution (live & verbose)#tcpdump -n -i ${dev} -vvnnXX#"}}},
        {"docker +", {{"login +", {{"*login user/pwd to dockerhub#docker login#dockerlogin"},
                                   {"*login user/pwd to specific registry#docker login ${self-hosted registry}#dockerlogin"}}},
                      {"settings +", {{"display system-wide info#docker info#"}, 
                                      {"*show all existed user configs for dockerd#cat /etc/docker/daemon.json#dockerd"}}},
                      {"image +", {{"show all images#docker images#"},
                                   {"*build img using dockerfile from current dir#docker build -t ${image}:${tag} .#dockerbuild"},
                                   {"*docker multi-stage build#see desc/dockerfile for details#dockermultistagebuild"}}},
                      {"history +", {{"show image build history(cmd/arg/env)#docker history ${image} -H#"}, 
                                     {"show image build history in verbose(cmd/arg/env)#docker history ${image} --no-trunc#"}}},
                      {"manifest +", {{"check whether img:tag already existed in remote, 0:existed, 1:none#docker manifest inspect ${img}:${tag} > /dev/null; echo $?#"}}},
                      {"container +", {{"show all containers(detailed)#docker ps -a#"},
                                       {"show all containers(only id)#docker ps -a -q#"}, 
                                       {"show a container wholesome info#docker container inspect ${id/name}#"}, 
                                       {"show a container pid#docker container inspect -f \"{{.State.Pid}}\" ${id/name}#"}, 
                                       {"show a container port mapping info#docker container port ${id/name}#"}, 
                                       {"show a container resource stat info#docker container stats --no-trunc ${id/name}#"}}},
                      {"run +", {{"start container with env var +", {{"*set env var from cmdline#docker run -e ${key}=${value} ${image}#dockerenvvar"},
                                                                     {"*set env var from file#docker run --env-file ${file} ${image}#dockerenvvar"}}},
                                 {"start container and remove it when exit#docker run --rm ${image}#"},
                                 {"*start container with perf tool PMU event collection enabled#docker run -it --security-opt seccomp=${perfenable.json} --rm ${image} bash#dockerperf"}}},
                      {"network +", {{"show docker network manager help info#docker network --help#"},
                                     {"show available network driver info#docker network ls#"},
                                     {"create a network in docker#docker network create ${networkname}#"},
                                     {"remove 1/more networks in docker#docker network rm ${networknames}#"},
                                     {"remove all unused networks in docker with prompt#docker network prune#"},
                                     {"show detailed info for a network driver by name/id#docker network inspect ${network name/id}#"}}},
                      {"port +", {{"list port mapping info of a container#docker port ${containerid}#"}}},
                      {"volumes +"},
                      {"files +"}}},
        {"file/dir operations +", {{"file permissions +", {{"change owner:group +", {{"change owner:group recursively for dir/subdir#sudo chown -R ${owner}:${group} ${dir}#"}}}, 
                                                           {"change rwx +"}}}, 
                                   {"zip/unzip file/dir +", {{"zip the dir to xxx.zip#zip -r ${zipfile}.zip ${dirtozip}#"}, 
                                                             {"unzip the xxx.zip#unzip ${zipfile}.zip#"}, 
                                                             {"unzip the xxx.zip to certain folder#unzip ${zipfile}.zip -d ${destdir}#"}}},
                                   {"tar +", {{"extract the content of xxx (tar)#tar -xvf ${xxx.tar}#"}, 
                                              {"extract the content of xxx compressed by gzip (tar.gz)#tar -xzvf ${xxx.tar.gz}#"}, 
                                              {"extract the content of xxx compressed by bzip2 (tar.bz2)#tar -xjvf ${xxx.tar.bz2#"}, 
                                              {"zip files under dir but excluding all files under certain folder using gzip#tar --exclude='*/${foldername}/*' -zcvf ${out.tgz} ${indir}#"}}},
                                   {"dir operations +", {{"create dir under $PWD#mkdir ${dirname}#"}, 
                                                         {"create dir under $PWD(recursively + no err even exist)#mkdir -p main/sub/last#"}, 
                                                         {"create dir under /(recursively + no err even exist)#mkdir -p /main/sub/last#"}}},
                                   {"scp +", {{"copy dir from local:dir to server:path#scp -r ${dir} ${user}@${ip}:${path}#"},
                                              {"copy file from local:file to server:path#scp ${file} ${user}@${ip}:${path}#"},
                                              {"copy dir from server:dir to local:path#scp -r ${user}@${ip}:${dir} ${path}#"},
                                              {"copy file from server:file to local:path#scp ${user}@${ip}:${file} ${localpath}#"}}}}},

        {"find +", {{"show manual of find#man find#"}, 
                    {"file operations +", {{"list files under cur dir#find . -type f#"},
                                           {"list files under cur dir matches the name pattern recursively#find . -type f -name '*.cpp'#"},
                                           {"list files under cur dir doesnt match the name pattern recursively#find . -type f ! -name '*.cpp'#"},
                                           {"list files under cur dir matches the name pattern at given level#find . -maxdepth ${level} -type f -name '*.cpp'#"},
                                           {"list files under cur dir but exclude ones under desc#find . -type f ! -path './desc/*'#"},
                                           {"remove files under cur dir but exclude ones under desc#find . -type f ! -path './desc/*' -exec rm -f {} +#"}}},
                    {"dir operations +", {{"list dirs under cur dir#find . -type d#"}, 
                                          {"list dirs under cur dir matches the name pattern recursively#find . -type d -name '*.cpp'#"}, 
                                          {"list dirs under cur dir doesnt match the name pattern recursively#find . -type d ! -name '*.cpp'#"}}}}},
        {"grep +"},
        {"nvim +", {{"nvim image +", {{"edit nvim dockerfile#nvim /Users/mac/nvim/Dockerfile#"},
                                      {"build nvim image##"},
                                      {"invoke nvim image by script##"}}},
                    {"nvim commands +"}}},
        {"tmux +", {{"settings +", {{"install"},{"config"}}},
                    {"session +", {{"create new session#tmux new -s ${session}#"},
                                   {"list sessions(terminal)#tmux ls#"},
                                   {"list sessions(tmux)#ctrl+b s#"},
                                   {"access sessions(terminal)#tmux a -t ${session}#"},
                                   {"kill session(terminal/tmux)#tmux kill-session -t ${session}#"},
                                   {"rename session(terminal/tmux)#tmux rename -t ${oldname} ${newname}#"},
                                   {"rename current session(tmux)#ctrl+b $#"}}},
                    {"window +", {{"create window#ctrl+b c#"},
                                  {"previous window#ctrl+b p#"},
                                  {"next window#ctrl+b n#"},
                                  {"switch to window n#ctrl+b ${win_num}#"},
                                  {"list windows#ctrl+b w#"},
                                  {"close current window#ctrl+b &#"}}},
                    {"pane +", {{"split win to left/right pane#ctrl+b %#"},
                                {"split win to top/bottom pane#ctrl+b \\#"},
                                {"select pane by arrow keys#ctrl+b ${arrows}#"},
                                {"maximize/restore current pane#ctrl+b z#"},
                                {"close current pane#ctrl+b x#"}}}}},
        {"crontab +", {{"show manual#man crontab#"},
                       {"show crontab configs#cat /etc/crontab#"},
                       {"list crontab jobs for current user#crontab -l#"},
                       {"edit/create crontab config for current user#crontab -e#"},
                       {"edit/create/replace crontab config for cur user in certain place#crontab ${path/file}#"},
                       {"remove all crontab jobs#crontab -r#"},
                       {"remove certain crontab job#crontab -r ${jobid}#"},
                       {"remove certain crontab job with prompt#crontab -ri#"}}},
        {"performance analysis +", {{"perf +", {{"list +", {{"list all supported events#perf list#"}, 
                                                            {"list hardware events#perf list hw#"}, 
                                                            {"list PMU (performance monitor unit) events#perf list pmu#"}}},
                                                {"record +", {{"record PMU event stat of certain process for a period#perf record -g -p ${pid} -- sleep ${time_to_record}#"},
                                                              {"record PMU event stat of binary executable at certain sampling rate#perf record -F 4000 -g -o perf.data ./out#"}}},
                                                {"report +", {{"report call-graph for generated perf file with statistics#perf report --stdio -ng#"}}},
                                                {"script +", {{"generate flamegreph using perf.data output#perf script | ./stackcollapse-perf.pl | ./flamegraph.pl > flame.svg#"}}}}}}},
        {"debug +", {{"gdb +", {{"show manual#http://www.yolinux.com/TUTORIALS/GDB-Commands.html#"}, 
                                {"enable gdb in tui mode#sudo gdb -tui out#"}, 
                                {"polling the win#ctrl+x; o#"}, 
                                {"select source code win#focus src#"}, 
                                {"select commandline win#focus cmd#"}, 
                                {"select assembly win#focus asm#"}, 
                                {"select register win#focus reg#"},
                                {"execute exact 1 line in source code#s (step)#"},
                                {"execute 1 line in source code#n (next)#"}, 
                                {"refresh tui win#ctrl+l#"},
                                {"call functions to check the result#call func(para1, para2...)#"}, 
                                {"disassemble 100bytes of instructions after $pc#disassemble $pc,+100#"}, 
                                {"disassemble 100bytes of instructions after function (e.g. main)#disassemble main,+100#"}, 
                                {"break at function#break ${function_name}#"}}},
                     {"pdb +", {{"list 11 lines around current line#l.#"},
                                {"list the code within the range [startline, endline]#l ${startline},${endline}#"}, 
                                {"list the code within the range [startline, startline+count] (only if count<startline)#l ${startline},${+count}#"}}},
                     {"valgrind +", {{"show manual#man valgrind#"}, 
                                     {"use memcheck tool for purpose of memory leak check#valgrind --tool=memcheck --leak-check=full ${path_to_program}#"}}}}},
        {"data serialization +", {{"json +"},
                                  {"yaml +", {{"*multiline string in yaml##yaml"}}}}},
        {"encryption +", {{"md5sum +", {{"show manual#man md5sum#"}}}, 
                          {"sha512sum +", {{"show manual#man sha512sum#"}}}}},
        {"ssh +", {{"ssh config#see desc/sshconfig for details#sshconfig"},
                   {"test ssh connection to github site without create new tty#ssh -T git@github.com#"}}},
        {"language +", {{"golang +", {{"show go help page#go --help#"},
                                      {"env +", {{"show go env help page#go help env#"},
                                                 {"list go env variables#go env#"},
                                                 {"show certain env variable value#go env ${env_var_name}#"},
                                                 {"change env var value (nothing change if value not valid)#go env -w ${env}=${value}#"}, 
                                                 {"usefull env configs +", {{"module are enabled regardless of whether a go.mod file is present, any directory without a go.mod file becomes its own module#go env -w GO111MODULE=on#"},
                                                                            {"modules are enabled if go.mod is present in cur/parent dir#go env -w GO111MODULE=auto#"},
                                                                            {"modules are disabled, use GOPATH for all imports#go env -w GO111MODULE=off#"}}}}},
                                      {"go mod +", {{"show help page#go help mod#"},
                                                    {"init cur dir as a module with name#go mod init ${modname}#"},
                                                    {"peeling module off cur dir#rm go.mod go.sum#"},
                                                    {"add missing & remove unused modules#go mod tidy#"},
                                                    {"show src -> dependency pairs of cur module#go mod graph#"}}},
                                      {"go get +", {{"show help page#go help get#"},
                                                    {"add package to cur module#go get ${pkgname}#"},
                                                    {"remove package downloaded#cd $GOPATH && del the related dir#"}}},
                                      {"go build +", {{"build the program#go build ${program.go}#"},
                                                      {"show help page#go help build#"},
                                                      {"show build cmd flow without actually build the program#go build -n ${program.go}#"},
                                                      {"show build cmd flow and build the program#go build -x ${program.go}#"},
                                                      {"build the program with data racing detection annotations#go build -race ${program.g}#"}}},
                                      {"gofmt +", {{"show auto format tool help#gofmt --help#"},
                                                   {"format go program and output in stdout#gofmt ${path/test.go}#"},
                                                   {"format go program in place#gofmt -w ${path/test.go}#"}}}}},
                        {"python +"},
                        {"c +"},
                        {"cpp +"}}},
        {"alpine +", {{"apk official doc site#https://wiki.alpinelinux.org/wiki/Main_Page#"}, 
                      {"apk info +", {{"show all installed apk#apk info#"}, 
                                      {"show all installed apk with 1line desc#apk -vv info#"}, 
                                      {"show detailed info of certain apk#apk info -a ${apk}#"}}}, 
                      {"show graphviz code for apk dependencies#apk dot ${apk}#"}}},
    };
    return menu_ptr;
}


