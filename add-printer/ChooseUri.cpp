/***************************************************************************
 *   Copyright (C) 2010 by Daniel Nicoletti                                *
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

#include "ChooseUri.h"
#include "ui_ChooseUri.h"

#include <KCupsRequest.h>

#include <KUrl>
#include <QStringBuilder>

#include <KDebug>

ChooseUri::ChooseUri(QWidget *parent) :
    GenericPage(parent),
    ui(new Ui::ChooseUri)
{
    ui->setupUi(this);

    // setup default options
    setWindowTitle(i18nc("@title:window", "Select a Printer to Add"));

    connect(ui->addressLE, SIGNAL(textChanged(QString)), this, SLOT(checkSelected()));
}

ChooseUri::~ChooseUri()
{
    delete ui;
}

void ChooseUri::setValues(const QVariantHash &args)
{
    m_args = args;
    KUrl url = args[KCUPS_DEVICE_URI].toString();

    if (url.url() != QLatin1String("other") && url.isValid()) {
        ui->addressLE->setText(url.url() % QLatin1String("://"));
    } else {
        ui->addressLE->clear();
    }
    ui->addressLE->setFocus();
}

QVariantHash ChooseUri::values() const
{
    QVariantHash ret = m_args;
    // URI might be scsi, network on anything that doesn't match before
    KUrl url(ui->addressLE->text());
    if (url.protocol().isEmpty() && ret[KCUPS_DEVICE_URI].toString() != QLatin1String("other")) {
        kDebug() << url;
        url.setProtocol(ret[KCUPS_DEVICE_URI].toString());
        kDebug() << url;
    }
    ret[KCUPS_DEVICE_URI] = url.url();
    return ret;
}

bool ChooseUri::isValid() const
{
    QVariantHash args = values();
    KUrl url(args[KCUPS_DEVICE_URI].toString());
kDebug() << url << url.isValid() << url.isEmpty() << url.protocol().isEmpty() << url.hasHost();
    return url.isValid() && !url.isEmpty() && !url.protocol().isEmpty() && url.hasHost();
}

bool ChooseUri::canProceed() const
{
    return isValid();
}

void ChooseUri::load()
{
}

void ChooseUri::checkSelected()
{
    emit allowProceed(isValid());
}
