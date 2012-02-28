/***************************************************************************
 *   Copyright (C) 2010-2012 by Daniel Nicoletti                           *
 *   dantti12@gmail.com                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; see the file COPYING. If not, write to       *
 *   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,  *
 *   Boston, MA 02110-1301, USA.                                           *
 ***************************************************************************/

#include "ConfigurePrinter.h"

#include <KDebug>
#include <KLocale>
#include <KAboutData>
#include <KCmdLineArgs>

int main(int argc, char **argv)
{
    KAboutData about("ConfigurePrinter",
                     "configure-printer",
                     ki18n("ConfigurePrinter"),
                     "0.1",
                     ki18n("ConfigurePrinter"),
                     KAboutData::License_GPL,
                     ki18n("(C) 2010-2012 Daniel Nicoletti"));

    about.addAuthor(ki18n("Daniel Nicoletti"), KLocalizedString(), "dantti12@gmail.com");

    KCmdLineArgs::init(argc, argv, &about);
    KCmdLineOptions options;
    options.add("configure-printer [printer name]", ki18n("Configure printer"));
    KCmdLineArgs::addCmdLineOptions(options);

    ConfigurePrinter::addCmdLineOptions();

    if (!ConfigurePrinter::start()) {
        //kDebug() << "ConfigurePrinter is already running!";
        return 0;
    }

    ConfigurePrinter app;
    return app.exec();
}