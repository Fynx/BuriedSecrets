/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include <cassert>
#include <cstdio>
#include <QtGui>

class DebugManager {
public:
	DebugManager() {}
};

// static const char *BashBlue   = "0;34";
static const char *BashGray   = "1;30";
static const char *BashGreen  = "0;32";
static const char *BashRed    = "0;31";
static const char *BashYellow = "0;33";

inline static QString bashColorStart(const char *bashColor)
{
	return QString("\033[") + QString(bashColor) + QString("m");
}

inline static QString bashColorEnd()
{
	return QString("\033[0m");
}

inline void print(const QString &str, const char *bashColor)
{
	fprintf(stderr, (bashColorStart(bashColor) + str + bashColorEnd() + "\n").toStdString().c_str());
}

inline void err(const QString &str)
{
	print(str, BashRed);
}

inline void warn(const QString &str)
{
	print(str, BashYellow);
}

inline void info(const QString &str)
{
	print(str, BashGreen);
}

inline void dataInfo(const QString &str)
{
	print(str, BashGray);
}
