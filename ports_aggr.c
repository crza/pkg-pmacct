/*
    pmacct (Promiscuous mode IP Accounting package)
    pmacct is Copyright (C) 2003-2005 by Paolo Lucente
*/

/*
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#define __PORTS_AGGR_C

/* includes */
#include "pmacct.h"
#include "pmacct-data.h"
#include "plugin_hooks.h"
#include "ports_aggr.h"
#include "util.h"

void load_ports(char *filename, struct ports_table *pt)
{
  FILE *file;
  char buf[8];
  int ret, rows = 0;

  if (filename) {
    if ((file = fopen(filename,"r")) == NULL) {
      Log(LOG_ERR, "ERROR: ports file '%s' not found\n", filename);
      exit(1); 
    }
    else {
      memset(pt, 0, sizeof(struct ports_table));

      while (!feof(file)) {
        if (fgets(buf, 8, file)) { 
	  rows++;
	  trim_spaces(buf);
	  if (!strlen(buf) || (buf[0] == '!')) continue;
	  ret = atoi(buf); 
	  if ((ret > 0) && (ret < PORTS_TABLE_ENTRIES)) pt->table[ret] = TRUE;
	  else Log(LOG_WARNING, "WARN: invalid port at %s:%d\n", filename, rows); 
	}
      }
    }
  }
}

