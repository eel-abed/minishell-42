# Minishell test of Diego
    
## exit
- is nesesary return value of exit
``` bash
exit 25
echo $?
->  25
```
- The value is nesesary to be in 
```bash 
    $?
```

## Erros in signals

-  Error in the ctr-\, in an empty prompt should not do anything.
-  ctrl-\ in a prompt after you wrote some stuff should not do anything.


## Erro in the export
- the caraters '?', "-", Ils ne peuvent pas être avant =, ça doit être après.

Before the equals sign (=)
Variable names must follow these rules:

Must start with:

- Letters (a-z, A-Z)
- Underscore (_)

Can contain:

- Letters (a-z, A-Z)
- Numbers (0-9)
- Underscore (_)
- NOT allowed before =:

Numbers at the start
- Special characters (!@#$%^&*()+-={}[]|:;"'<>,?/)
- Spaces
- Hyphens (-)
- Question marks (?)
- After the equals sign (=)
- Almost any character is allowed:

- All special characters
- Spaces (if quoted)
- Numbers
- Punctuation marks
- Special characters




## Error un Double Quotes:
- you need always return wih the ", the comands,
```bash
echo "cat lol.c | cat > lol.c"
Token[0]:
  Value: [echo]
  Type:  [0]
------------------------
Token[1]:
  Value: ["cat lol.c | cat > lol.c"]
  Type:  [0]
------------------------
Token[0]:
  Value: [echo]
  Type:  [0]
------------------------
Token[1]:
  Value: [cat lol.c | cat > lol.c]
  Type:  [0]
------------------------
Token[0]:
  Value: [echo cat lol.c | cat > lol.c]
  Type:  [0]
------------------------
```

## Error in the exit:

- in the moment use exit is a big error:

```bash

minishell> echo "cat lol.c | cat > lol.c"
Token[0]:
  Value: [echo]
  Type:  [0]
------------------------
Token[1]:
  Value: ["cat lol.c | cat > lol.c"]
  Type:  [0]
------------------------
Token[0]:
  Value: [echo]
  Type:  [0]
------------------------
Token[1]:
  Value: [cat lol.c | cat > lol.c]
  Type:  [0]
------------------------
Token[0]:
  Value: [echo cat lol.c | cat > lol.c]
  Type:  [0]
------------------------
minishell> 111
Token[0]:
  Value: [111
]
  Type:  [0]
------------------------
Token[0]:
  Value: [111
]
  Type:  [0]
------------------------
Token[0]:
  Value: [111
]
  Type:  [0]
------------------------
111
: command not found
minishell> export 
Token[0]:
  Value: [export]
  Type:  [0]
------------------------
Token[0]:
  Value: [export]
  Type:  [0]
------------------------
Token[0]:
  Value: [export]
  Type:  [0]
------------------------
export GJS_DEBUG_TOPICS="JS ERROR;JS LOG"
export USER="mafourni"
export XDG_SESSION_TYPE="x11"
export SHLVL="1"
export HOME="/home/mafourni"
export DESKTOP_SESSION="ubuntu"
export GIO_LAUNCHED_DESKTOP_FILE="/usr/share/applications/code.desktop"
export GTK_MODULES="gail:atk-bridge"
export XDG_SEAT_PATH="/org/freedesktop/DisplayManager/Seat0"
export MANAGERPID="3385688"
export SYSTEMD_EXEC_PID="3386310"
export DBUS_SESSION_BUS_ADDRESS="unix:path=/run/user/110509/bus"
export LIBVIRT_DEFAULT_URI="qemu:///system"
export GIO_LAUNCHED_DESKTOP_FILE_PID="3387609"
export LOGNAME="mafourni"
export GTK_IM_MODULE="ibus"
export JOURNAL_STREAM="8:55854813"
export XDG_SESSION_CLASS="user"
export GNOME_DESKTOP_SESSION_ID="this-is-deprecated"
export PATH="/home/mafourni/.local/funcheck/host:/home/mafourni/bin:/home/mafourni/.local/funcheck/host:/home/mafourni/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/mafourni/.config/Code/User/globalStorage/github.copilot-chat/debugCommand"
export SESSION_MANAGER="local/paul-f4Br6s7.clusters.42paris.fr:@/tmp/.ICE-unix/3386287,unix/paul-f4Br6s7.clusters.42paris.fr:/tmp/.ICE-unix/3386287"
export INVOCATION_ID="1165e4c0fad347e4a645fd508a880b7d"
export XDG_RUNTIME_DIR="/run/user/110509"
export XDG_MENU_PREFIX="gnome-"
export XDG_SESSION_PATH="/org/freedesktop/DisplayManager/Session154"
export DISPLAY=":0"
export LANG="en_US.UTF-8"
export XDG_CURRENT_DESKTOP="Unity"
export XAUTHORITY="/home/mafourni/.Xauthority"
export XDG_SESSION_DESKTOP="ubuntu"
export XMODIFIERS="@im=ibus"
export SSH_AGENT_LAUNCHER="gnome-keyring"
export SSH_AUTH_SOCK="/run/user/110509/keyring/ssh"
export XDG_GREETER_DATA_DIR="/var/lib/lightdm-data/mafourni"
export SHELL="/bin/zsh"
export KRB5CCNAME="FILE:/tmp/krb5cc_110509_r42dyK"
export QT_ACCESSIBILITY="1"
export GDMSESSION="ubuntu"
export DOCKER_HOST="unix:///run/user/110509/docker.sock"
export GPG_AGENT_INFO="/run/user/110509/gnupg/S.gpg-agent:0:1"
export GJS_DEBUG_OUTPUT="stderr"
export QT_IM_MODULE="ibus"
export PWD="/home/mafourni/Desktop/MINISHELL"
export XDG_DATA_DIRS="/usr/share/ubuntu:/usr/share/gnome:/home/mafourni/.local/share/flatpak/exports/share:/var/lib/flatpak/exports/share:/usr/local/share:/usr/share:/var/lib/snapd/desktop"
export XDG_CONFIG_DIRS="/etc/xdg/xdg-ubuntu:/etc/xdg"
export CHROME_DESKTOP="code.desktop"
export ORIGINAL_XDG_CURRENT_DESKTOP="ubuntu:GNOME"
export GDK_BACKEND="x11"
export OLDPWD="/home/mafourni/Desktop/MINISHELL"
export ZSH="/home/mafourni/.oh-my-zsh"
export PAGER="less"
export LESS="-R"
export LSCOLORS="Gxfxcxdxbxegedabagacad"
export LS_COLORS="rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.webp=
minishell> export "diego=queso"'-test=20'111
Token[0]:
  Value: [export]
  Type:  [0]
------------------------
minishell> env
Token[0]:
  Value: [env]
  Type:  [0]
------------------------
Token[0]:
  Value: [env]
  Type:  [0]
------------------------
Token[0]:
  Value: [env]
  Type:  [0]
------------------------
GJS_DEBUG_TOPICS=JS ERROR;JS LOG
USER=mafourni
XDG_SESSION_TYPE=x11
SHLVL=1
HOME=/home/mafourni
DESKTOP_SESSION=ubuntu
GIO_LAUNCHED_DESKTOP_FILE=/usr/share/applications/code.desktop
GTK_MODULES=gail:atk-bridge
XDG_SEAT_PATH=/org/freedesktop/DisplayManager/Seat0
MANAGERPID=3385688
SYSTEMD_EXEC_PID=3386310
DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/110509/bus
LIBVIRT_DEFAULT_URI=qemu:///system
GIO_LAUNCHED_DESKTOP_FILE_PID=3387609
LOGNAME=mafourni
GTK_IM_MODULE=ibus
JOURNAL_STREAM=8:55854813
XDG_SESSION_CLASS=user
GNOME_DESKTOP_SESSION_ID=this-is-deprecated
PATH=/home/mafourni/.local/funcheck/host:/home/mafourni/bin:/home/mafourni/.local/funcheck/host:/home/mafourni/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/mafourni/.config/Code/User/globalStorage/github.copilot-chat/debugCommand
SESSION_MANAGER=local/paul-f4Br6s7.clusters.42paris.fr:@/tmp/.ICE-unix/3386287,unix/paul-f4Br6s7.clusters.42paris.fr:/tmp/.ICE-unix/3386287
INVOCATION_ID=1165e4c0fad347e4a645fd508a880b7d
XDG_RUNTIME_DIR=/run/user/110509
XDG_MENU_PREFIX=gnome-
XDG_SESSION_PATH=/org/freedesktop/DisplayManager/Session154
DISPLAY=:0
LANG=en_US.UTF-8
XDG_CURRENT_DESKTOP=Unity
XAUTHORITY=/home/mafourni/.Xauthority
XDG_SESSION_DESKTOP=ubuntu
XMODIFIERS=@im=ibus
SSH_AGENT_LAUNCHER=gnome-keyring
SSH_AUTH_SOCK=/run/user/110509/keyring/ssh
XDG_GREETER_DATA_DIR=/var/lib/lightdm-data/mafourni
SHELL=/bin/zsh
KRB5CCNAME=FILE:/tmp/krb5cc_110509_r42dyK
QT_ACCESSIBILITY=1
GDMSESSION=ubuntu
DOCKER_HOST=unix:///run/user/110509/docker.sock
GPG_AGENT_INFO=/run/user/110509/gnupg/S.gpg-agent:0:1
GJS_DEBUG_OUTPUT=stderr
QT_IM_MODULE=ibus
PWD=/home/mafourni/Desktop/MINISHELL
XDG_DATA_DIRS=/usr/share/ubuntu:/usr/share/gnome:/home/mafourni/.local/share/flatpak/exports/share:/var/lib/flatpak/exports/share:/usr/local/share:/usr/share:/var/lib/snapd/desktop
XDG_CONFIG_DIRS=/etc/xdg/xdg-ubuntu:/etc/xdg
CHROME_DESKTOP=code.desktop
ORIGINAL_XDG_CURRENT_DESKTOP=ubuntu:GNOME
GDK_BACKEND=x11
OLDPWD=/home/mafourni/Desktop/MINISHELL
ZSH=/home/mafourni/.oh-my-zsh
PAGER=less
LESS=-R
LSCOLORS=Gxfxcxdxbxegedabagacad
LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.webp=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:
_=/home/mafourni/Desktop/MINISHELL/./minishell
TERM_PROGRAM=vscode
TERM_PROGRAM_VERSION=1.97.2
COLORTERM=truecolor
GIT_ASKPASS=/usr/share/code/resources/app/extensions/git/dist/askpass.sh
VSCODE_GIT_ASKPASS_NODE=/usr/share/code/code
VSCODE_GIT_ASKPASS_EXTRA_ARGS=
VSCODE_GIT_ASKPASS_MAIN=/usr/share/code/resources/app/extensions/git/dist/askpass-main.js
VSCODE_GIT_IPC_HANDLE=/run/user/110509/vscode-git-fbac876e57.sock
VSCODE_INJECTION=1
ZDOTDIR=/home/mafourni
USER_ZDOTDIR=/home/mafourni
TERM=xterm-256color
diego=queso-test=2011

minishell> env quesop
Token[0]:
  Value: [env]
  Type:  [0]
------------------------
Token[1]:
  Value: [quesop]
  Type:  [0]
------------------------
Token[0]:
  Value: [env]
  Type:  [0]
------------------------
Token[1]:
  Value: [quesop]
  Type:  [0]
------------------------
Token[0]:
  Value: [env quesop]
  Type:  [0]
------------------------
GJS_DEBUG_TOPICS=JS ERROR;JS LOG
USER=mafourni
XDG_SESSION_TYPE=x11
SHLVL=1
HOME=/home/mafourni
DESKTOP_SESSION=ubuntu
GIO_LAUNCHED_DESKTOP_FILE=/usr/share/applications/code.desktop
GTK_MODULES=gail:atk-bridge
XDG_SEAT_PATH=/org/freedesktop/DisplayManager/Seat0
MANAGERPID=3385688
SYSTEMD_EXEC_PID=3386310
DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/110509/bus
LIBVIRT_DEFAULT_URI=qemu:///system
GIO_LAUNCHED_DESKTOP_FILE_PID=3387609
LOGNAME=mafourni
GTK_IM_MODULE=ibus
JOURNAL_STREAM=8:55854813
XDG_SESSION_CLASS=user
GNOME_DESKTOP_SESSION_ID=this-is-deprecated
PATH=/home/mafourni/.local/funcheck/host:/home/mafourni/bin:/home/mafourni/.local/funcheck/host:/home/mafourni/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/mafourni/.config/Code/User/globalStorage/github.copilot-chat/debugCommand
SESSION_MANAGER=local/paul-f4Br6s7.clusters.42paris.fr:@/tmp/.ICE-unix/3386287,unix/paul-f4Br6s7.clusters.42paris.fr:/tmp/.ICE-unix/3386287
INVOCATION_ID=1165e4c0fad347e4a645fd508a880b7d
XDG_RUNTIME_DIR=/run/user/110509
XDG_MENU_PREFIX=gnome-
XDG_SESSION_PATH=/org/freedesktop/DisplayManager/Session154
DISPLAY=:0
LANG=en_US.UTF-8
XDG_CURRENT_DESKTOP=Unity
XAUTHORITY=/home/mafourni/.Xauthority
XDG_SESSION_DESKTOP=ubuntu
XMODIFIERS=@im=ibus
SSH_AGENT_LAUNCHER=gnome-keyring
SSH_AUTH_SOCK=/run/user/110509/keyring/ssh
XDG_GREETER_DATA_DIR=/var/lib/lightdm-data/mafourni
SHELL=/bin/zsh
KRB5CCNAME=FILE:/tmp/krb5cc_110509_r42dyK
QT_ACCESSIBILITY=1
GDMSESSION=ubuntu
DOCKER_HOST=unix:///run/user/110509/docker.sock
GPG_AGENT_INFO=/run/user/110509/gnupg/S.gpg-agent:0:1
GJS_DEBUG_OUTPUT=stderr
QT_IM_MODULE=ibus
PWD=/home/mafourni/Desktop/MINISHELL
XDG_DATA_DIRS=/usr/share/ubuntu:/usr/share/gnome:/home/mafourni/.local/share/flatpak/exports/share:/var/lib/flatpak/exports/share:/usr/local/share:/usr/share:/var/lib/snapd/desktop
XDG_CONFIG_DIRS=/etc/xdg/xdg-ubuntu:/etc/xdg
CHROME_DESKTOP=code.desktop
ORIGINAL_XDG_CURRENT_DESKTOP=ubuntu:GNOME
GDK_BACKEND=x11
OLDPWD=/home/mafourni/Desktop/MINISHELL
ZSH=/home/mafourni/.oh-my-zsh
PAGER=less
LESS=-R
LSCOLORS=Gxfxcxdxbxegedabagacad
LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.webp=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:
_=/home/mafourni/Desktop/MINISHELL/./minishell
TERM_PROGRAM=vscode
TERM_PROGRAM_VERSION=1.97.2
COLORTERM=truecolor
GIT_ASKPASS=/usr/share/code/resources/app/extensions/git/dist/askpass.sh
VSCODE_GIT_ASKPASS_NODE=/usr/share/code/code
VSCODE_GIT_ASKPASS_EXTRA_ARGS=
VSCODE_GIT_ASKPASS_MAIN=/usr/share/code/resources/app/extensions/git/dist/askpass-main.js
VSCODE_GIT_IPC_HANDLE=/run/user/110509/vscode-git-fbac876e57.sock
VSCODE_INJECTION=1
ZDOTDIR=/home/mafourni
USER_ZDOTDIR=/home/mafourni
TERM=xterm-256color
diego=queso-test=2011

minishell> env -al
Token[0]:
  Value: [env]
  Type:  [0]
------------------------
Token[1]:
  Value: [-al]
  Type:  [0]
------------------------
Token[0]:
  Value: [env]
  Type:  [0]
------------------------
Token[1]:
  Value: [-al]
  Type:  [0]
------------------------
Token[0]:
  Value: [env -al]
  Type:  [0]
------------------------
GJS_DEBUG_TOPICS=JS ERROR;JS LOG
USER=mafourni
XDG_SESSION_TYPE=x11
SHLVL=1
HOME=/home/mafourni
DESKTOP_SESSION=ubuntu
GIO_LAUNCHED_DESKTOP_FILE=/usr/share/applications/code.desktop
GTK_MODULES=gail:atk-bridge
XDG_SEAT_PATH=/org/freedesktop/DisplayManager/Seat0
MANAGERPID=3385688
SYSTEMD_EXEC_PID=3386310
DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/110509/bus
LIBVIRT_DEFAULT_URI=qemu:///system
GIO_LAUNCHED_DESKTOP_FILE_PID=3387609
LOGNAME=mafourni
GTK_IM_MODULE=ibus
JOURNAL_STREAM=8:55854813
XDG_SESSION_CLASS=user
GNOME_DESKTOP_SESSION_ID=this-is-deprecated
PATH=/home/mafourni/.local/funcheck/host:/home/mafourni/bin:/home/mafourni/.local/funcheck/host:/home/mafourni/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/mafourni/.config/Code/User/globalStorage/github.copilot-chat/debugCommand
SESSION_MANAGER=local/paul-f4Br6s7.clusters.42paris.fr:@/tmp/.ICE-unix/3386287,unix/paul-f4Br6s7.clusters.42paris.fr:/tmp/.ICE-unix/3386287
INVOCATION_ID=1165e4c0fad347e4a645fd508a880b7d
XDG_RUNTIME_DIR=/run/user/110509
XDG_MENU_PREFIX=gnome-
XDG_SESSION_PATH=/org/freedesktop/DisplayManager/Session154
DISPLAY=:0
LANG=en_US.UTF-8
XDG_CURRENT_DESKTOP=Unity
XAUTHORITY=/home/mafourni/.Xauthority
XDG_SESSION_DESKTOP=ubuntu
minishell> exit
Token[0]:
  Value: [exit]
  Type:  [0]
------------------------
Token[0]:
  Value: [exit]
  Type:  [0]
------------------------
Token[0]:
  Value: [exit]
  Type:  [0]
------------------------
exit
double free or corruption (fasttop)
[1]    3402844 IOT instruction (core dumped)  ./minishell

```
