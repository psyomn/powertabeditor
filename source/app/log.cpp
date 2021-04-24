/*
  * Copyright (C) 2021 Simon Symeonidis
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "log.h"
#include "paths.h"

#include <cstdio>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iostream>
#include <mutex>

namespace Log {
// destructor should close the file when main exits
// note: might not capture critical errors, but this should be a good
// enought start...
std::ofstream logFile(Paths::getLogPath().string(),
                      std::ofstream::app);

// since Log::Output will capture anything that is coming in from
// qDebug and friends, we might intercept messages asynchronously and
// may result in data races around logFile
std::mutex logFileMutex;

std::string logContents() {
    std::ifstream file(Paths::getLogPath().string());
    std::cout << std::string(Paths::getLogPath().string()) << std::endl;
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

void Output(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // Since this intercepts
    std::lock_guard lock(logFileMutex);

    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";

    std::string timestamp;
    {
        char output[64] = {0};
        const auto now = std::time(0);
        const auto *tmp = localtime(&now);
        strftime(output, sizeof(output), "%Y/%m/%dT%H:%M:%S", tmp);
        timestamp = std::string(output);
    }

    auto logFn = [&](std::string label,
                     std::ostream& ofile,
                     std::ostream& oterminal)-> void
    {
        ofile
            << timestamp << " "
            << label << ": "
            << localMsg.constData() << " "
            << file << " "
            << context.line << " "
            << function << std::endl;

        oterminal
            << timestamp << " "
            << label << ": "
            << localMsg.constData() << " "
            << file << " "
            << context.line << " "
            << function << std::endl;
    };

    switch (type) {
    case QtDebugMsg:
        logFn("debug", logFile, std::cerr);
        break;
    case QtInfoMsg:
        logFn("info", logFile, std::cout);
        break;
    case QtWarningMsg:
        logFn("warning", logFile, std::cerr);
        break;
    case QtCriticalMsg:
        logFn("critical", logFile, std::cerr);
        break;
    case QtFatalMsg:
        logFn("fatal", logFile, std::cerr);
        break;
    }
}
}
