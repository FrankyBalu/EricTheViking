/*
 * libEric
 * Copyright (C) 2022   Frank Kartheuser <frank.kartheuser1988@gmail.com>
 * Copyright (C) 2023   Frank Kartheuser <frank.kartheuser1988@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef __LOG
#define __LOG

#include <plog/Log.h>

namespace LibEric {

/**
 * @brief Initialisiert den logger
 *
 * @param logLevel gibt an, was ausgegeben werden soll
 *                  none = Es wird garnix ausgegeben\n
 *                  fatal = Es werden nur Meldungen ausgegeben, wenn das Programm beendet werden muss\n
 *                  error = Irgendwas ist schief gelaufen, aber das Programm kann (wahrscheinlich) weiter laufen\n
 *                  warning = Hier sollte nachgebessert werden, meist Logik Fehler\n
 *                  info = Dem Nutzer wird gesagt, was wir gerade machen\n
 *                  debug = Zusätzliche ausgaben, die sich eher an Entwickler richten\n
 *                  verbos = Informationen die wahrscheinlich keiner wissen will
 * @return nix
 */
void InitLog(plog::Severity logLevel);

}; //namespace LibEric
#endif //__LOG
