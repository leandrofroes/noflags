/*
* 	noflags - A simple tool to disable ASLR and DEP bits in DLL Characteristics 
*
* 	Author: Leandro Fróes
*
*	Copyright (C) 2019 Leandro Fróes
*
*	This program is free software: you can redistribute it and/or modify
*	it under the terms of the GNU General Public License as published by
*	the Free Software Foundation, either version 3 of the License, or
*	(at your option) any later version.
*	This program is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*	GNU General Public License for more details.
*	You should have received a copy of the GNU General Public License
*	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>

#define ASLR_BIT 6
#define NX_BIT 8

void usage(){
  fprintf(stderr, "Usage: noflags <filename>\n");
  exit(1);
}

void error(const char *msg){
  fprintf(stderr, "Error: %s\n", msg);
  exit(1);
}

int main(int argc, char **argv){

  if(argc < 2)
    usage();

  FILE *fp;
  unsigned int e_lfanew = 0x3c;
  unsigned int signature;
  unsigned int flags_pos;
  unsigned short int new_flags;

  fp = fopen(argv[1], "r+");

  if(fp == NULL)
    error("Fail to open the file!");

  if(fseek(fp, e_lfanew, SEEK_SET))
    error("Fail parsing the file");

  fread(&signature, sizeof(signature), 1, fp);

  flags_pos = signature + 0x5E;

  if(fseek(fp, flags_pos, SEEK_SET))
    error("Fail parsing the file");

  fread(&new_flags, sizeof(new_flags), 1, fp);

  if(fseek(fp, flag_pos, SEEK_SET))
    error("Fail parsing the file");
  
  new_flags &= ~(1 << ASLR_BIT);
  new_flags &= ~(1 << NX_BIT);

  if(!fwrite((const void *)&new_flags, sizeof(new_flags), 1, fp))
    error("Fail to set flags!");

  fclose(fp);

  return 0;

}
