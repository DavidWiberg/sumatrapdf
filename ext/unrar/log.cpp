#include "rar.hpp"


static wchar LogName[NM];

void InitLogOptions(const wchar *LogFileName)
{
  wcsncpyz(LogName,LogFileName,ASIZE(LogName));
}


#ifndef SILENT
void Log(const wchar *ArcName,const wchar *fmt,...)
{
  // Preserve the error code for possible following system error message.
  int Code=ErrHandler.GetSystemErrorCode();

  Alarm();

  // This buffer is for format string only, not for entire output,
  // so it can be short enough.
  wchar fmtw[1024];
  PrintfPrepareFmt(fmt,fmtw,ASIZE(fmtw));

  safebuf wchar Msg[2*NM+1024];
  va_list arglist;
  va_start(arglist,fmt);
  vswprintf(Msg,ASIZE(Msg),fmtw,arglist);
  va_end(arglist);
  eprintf(L"%ls",Msg);
  ErrHandler.SetSystemErrorCode(Code);
}
#endif


