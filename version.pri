PROJECT_NAME = qbittorrent
PROJECT_VERSION = 3.0.0alpha

os2 {
    DEFINES += VERSION=\'\"v$${PROJECT_VERSION}\"\'
} else {
    DEFINES += VERSION=\\\"v$${PROJECT_VERSION}\\\"
}

DEFINES += VERSION_MAJOR=3
DEFINES += VERSION_MINOR=0
DEFINES += VERSION_BUGFIX=0
