//---------------------------------------------------------------------------
#ifndef CommonH
#define CommonH
//---------------------------------------------------------------------------
#define EXCEPTION throw ExtException(NULL, L"")
#define THROWOSIFFALSE(C) if (!(C)) RaiseLastOSError();
#define SAFE_DESTROY_EX(CLASS, OBJ) { CLASS * PObj = OBJ; OBJ = NULL; delete PObj; }
#define SAFE_DESTROY(OBJ) SAFE_DESTROY_EX(TObject, OBJ)
#define ASCOPY(dest, source) \
  { \
    AnsiString CopyBuf = source; \
    strncpy(dest, CopyBuf.c_str(), LENOF(dest)); \
    dest[LENOF(dest)-1] = '\0'; \
  }
#define FORMAT(S, F) Format(S, ARRAYOFCONST(F))
#define FMTLOAD(I, F) FmtLoadStr(I, ARRAYOFCONST(F))
#define LENOF(x) ( (sizeof((x))) / (sizeof(*(x))))
#define FLAGSET(SET, FLAG) (((SET) & (FLAG)) == (FLAG))
#define FLAGCLEAR(SET, FLAG) (((SET) & (FLAG)) == 0)
#define FLAGMASK(ENABLE, FLAG) ((ENABLE) ? (FLAG) : 0)
#define SWAP(TYPE, FIRST, SECOND) \
  { TYPE __Backup = FIRST; FIRST = SECOND; SECOND = __Backup; }
//---------------------------------------------------------------------------
extern const wchar_t EngShortMonthNames[12][4];
extern const char Bom[3];
extern const wchar_t TokenPrefix;
extern const wchar_t NoReplacement;
extern const wchar_t TokenReplacement;
extern const UnicodeString LocalInvalidChars;
//---------------------------------------------------------------------------
UnicodeString ReplaceChar(UnicodeString Str, wchar_t A, wchar_t B);
UnicodeString DeleteChar(UnicodeString Str, wchar_t C);
void PackStr(UnicodeString &Str);
void PackStr(RawByteString &Str);
UnicodeString MakeValidFileName(UnicodeString FileName);
UnicodeString RootKeyToStr(HKEY RootKey);
UnicodeString BooleanToStr(bool B);
UnicodeString BooleanToEngStr(bool B);
UnicodeString DefaultStr(const UnicodeString & Str, const UnicodeString & Default);
UnicodeString CutToChar(UnicodeString &Str, wchar_t Ch, bool Trim);
UnicodeString CopyToChars(const UnicodeString & Str, int & From, UnicodeString Chs, bool Trim,
  wchar_t * Delimiter = NULL, bool DoubleDelimiterEscapes = false);
UnicodeString DelimitStr(UnicodeString Str, UnicodeString Chars);
UnicodeString ShellDelimitStr(UnicodeString Str, wchar_t Quote);
UnicodeString ExceptionLogString(Exception *E);
bool IsNumber(const UnicodeString Str);
UnicodeString __fastcall SystemTemporaryDirectory();
UnicodeString __fastcall GetShellFolderPath(int CSIdl);
UnicodeString __fastcall StripPathQuotes(const UnicodeString Path);
UnicodeString __fastcall AddPathQuotes(UnicodeString Path);
void __fastcall SplitCommand(UnicodeString Command, UnicodeString &Program,
  UnicodeString & Params, UnicodeString & Dir);
UnicodeString __fastcall ValidLocalFileName(UnicodeString FileName);
UnicodeString __fastcall ValidLocalFileName(
  UnicodeString FileName, wchar_t InvalidCharsReplacement,
  const UnicodeString & TokenizibleChars, const UnicodeString & LocalInvalidChars);
UnicodeString __fastcall ExtractProgram(UnicodeString Command);
UnicodeString __fastcall FormatCommand(UnicodeString Program, UnicodeString Params);
UnicodeString __fastcall ExpandFileNameCommand(const UnicodeString Command,
  const UnicodeString FileName);
void __fastcall ReformatFileNameCommand(UnicodeString & Command);
UnicodeString __fastcall EscapePuttyCommandParam(UnicodeString Param);
UnicodeString __fastcall ExpandEnvironmentVariables(const UnicodeString & Str);
bool __fastcall ComparePaths(const UnicodeString & Path1, const UnicodeString & Path2);
bool __fastcall CompareFileName(const UnicodeString & Path1, const UnicodeString & Path2);
bool __fastcall IsReservedName(UnicodeString FileName);
UnicodeString __fastcall DisplayableStr(const RawByteString & Str);
UnicodeString __fastcall ByteToHex(unsigned char B, bool UpperCase = true);
UnicodeString __fastcall BytesToHex(const unsigned char * B, size_t Length, bool UpperCase = true, wchar_t Separator = L'\0');
UnicodeString __fastcall BytesToHex(RawByteString Str, bool UpperCase = true, wchar_t Separator = L'\0');
UnicodeString __fastcall CharToHex(wchar_t Ch, bool UpperCase = true);
RawByteString __fastcall HexToBytes(const UnicodeString Hex);
unsigned char __fastcall HexToByte(const UnicodeString Hex);
UnicodeString __fastcall DecodeUrlChars(UnicodeString S);
UnicodeString __fastcall EncodeUrlChars(UnicodeString S, UnicodeString Ignore = L"");
UnicodeString __fastcall EncodeUrlString(UnicodeString S);
bool __fastcall RecursiveDeleteFile(const UnicodeString FileName, bool ToRecycleBin);
unsigned int __fastcall CancelAnswer(unsigned int Answers);
unsigned int __fastcall AbortAnswer(unsigned int Answers);
unsigned int __fastcall ContinueAnswer(unsigned int Answers);
UnicodeString __fastcall LoadStr(int Ident, unsigned int MaxLength);
UnicodeString __fastcall LoadStrPart(int Ident, int Part);
UnicodeString __fastcall EscapeHotkey(const UnicodeString & Caption);
bool __fastcall CutToken(UnicodeString & Str, UnicodeString & Token);
void __fastcall AddToList(UnicodeString & List, const UnicodeString & Value, const UnicodeString & Delimiter);
bool __fastcall Is2000();
bool __fastcall IsWin7();
bool __fastcall IsExactly2008R2();
TLibModule * __fastcall FindModule(void * Instance);
__int64 __fastcall Round(double Number);
bool __fastcall TryRelativeStrToDateTime(UnicodeString S, TDateTime & DateTime);
LCID __fastcall GetDefaultLCID();
UnicodeString DefaultEncodingName();
//---------------------------------------------------------------------------
typedef void __fastcall (__closure* TProcessLocalFileEvent)
  (const UnicodeString FileName, const TSearchRec Rec, void * Param);
bool __fastcall FileSearchRec(const UnicodeString FileName, TSearchRec & Rec);
void __fastcall ProcessLocalDirectory(UnicodeString DirName,
  TProcessLocalFileEvent CallBackFunc, void * Param = NULL, int FindAttrs = -1);
//---------------------------------------------------------------------------
enum TDSTMode
{
  dstmWin =  0, //
  dstmUnix = 1, // adjust UTC time to Windows "bug"
  dstmKeep = 2
};
bool __fastcall UsesDaylightHack();
TDateTime __fastcall EncodeDateVerbose(Word Year, Word Month, Word Day);
TDateTime __fastcall EncodeTimeVerbose(Word Hour, Word Min, Word Sec, Word MSec);
TDateTime __fastcall UnixToDateTime(__int64 TimeStamp, TDSTMode DSTMode);
FILETIME __fastcall DateTimeToFileTime(const TDateTime DateTime, TDSTMode DSTMode);
TDateTime __fastcall AdjustDateTimeFromUnix(TDateTime DateTime, TDSTMode DSTMode);
void __fastcall UnifyDateTimePrecision(TDateTime & DateTime1, TDateTime & DateTime2);
TDateTime __fastcall FileTimeToDateTime(const FILETIME & FileTime);
__int64 __fastcall ConvertTimestampToUnix(const FILETIME & FileTime,
  TDSTMode DSTMode);
TDateTime __fastcall ConvertTimestampToUTC(TDateTime DateTime);
__int64 __fastcall ConvertTimestampToUnixSafe(const FILETIME & FileTime,
  TDSTMode DSTMode);
UnicodeString __fastcall FixedLenDateTimeFormat(const UnicodeString & Format);
int __fastcall CompareFileTime(TDateTime T1, TDateTime T2);
//---------------------------------------------------------------------------
template<class MethodT>
MethodT __fastcall MakeMethod(void * Data, void * Code)
{
  MethodT Method;
  ((TMethod*)&Method)->Data = Data;
  ((TMethod*)&Method)->Code = Code;
  return Method;
}
//---------------------------------------------------------------------------
class TGuard
{
public:
  __fastcall TGuard(TCriticalSection * ACriticalSection);
  __fastcall ~TGuard();

private:
  TCriticalSection * FCriticalSection;
};
//---------------------------------------------------------------------------
class TUnguard
{
public:
  __fastcall TUnguard(TCriticalSection * ACriticalSection);
  __fastcall ~TUnguard();

private:
  TCriticalSection * FCriticalSection;
};
//---------------------------------------------------------------------------
//!CLEANBEGIN
#include <tchar.h>
#define TRACING  (_TRACE,_TRACEFMT,Callstack,__callstack)
#define NOTRACING  (_TRACE_FAKE, _TRACEFMT_FAKE, , )
#define _TRACING_TRACE(TRACE, TRACEFMT, CALLSTACK, CALLSTACKI) TRACE
#define _TRACING_TRACEFMT(TRACE, TRACEFMT, CALLSTACK, CALLSTACKI) TRACEFMT
#define _TRACING_CALLSTACK(TRACE, TRACEFMT, CALLSTACK, CALLSTACKI) CALLSTACK
#define _TRACING_CALLSTACKI(TRACE, TRACEFMT, CALLSTACK, CALLSTACKI) CALLSTACKI
#define _TRACE(SOURCE, FUNC, LINE, MESSAGE) \
  if (IsTracing) Trace(TEXT(__FILE__), TEXT(__FUNC__), __LINE__, (MESSAGE))
#define _TRACEFMT(SOURCE, FUNC, LINE, FORMAT, PARAMS) \
  if (IsTracing) TraceFmt(TEXT(__FILE__), TEXT(__FUNC__), __LINE__, (FORMAT), PARAMS)
#define _TRACE_FAKE(SOURCE, FUNC, LINE, MESSAGE)
#define _TRACEFMT_FAKE(SOURCE, FUNC, LINE, FORMAT, PARAMS)

#ifdef _DEBUG
void __fastcall SetTraceFile(HANDLE TraceFile);
#define TRACEENV "WINSCPTRACE"
extern bool IsTracing;
const unsigned int CallstackTlsOff = (unsigned int)-1;
extern unsigned int CallstackTls;
void __fastcall Trace(const wchar_t * SourceFile, const wchar_t * Func,
  int Line, const wchar_t * Message);
void __fastcall TraceFmt(const wchar_t * SourceFile, const wchar_t * Func,
  int Line, const wchar_t * Format, TVarRec * Args, const int Args_Size);
#define CTRACEIMPL(TRACING, MESSAGE) \
  _TRACING_TRACE TRACING (TEXT(__FILE__), TEXT(__FUNC__), __LINE__, (MESSAGE))
#define CTRACEFMTIMPL(TRACING, MESSAGE, PARAMS) \
  _TRACING_TRACEFMT TRACING (TEXT(__FILE__), TEXT(__FUNC__), __LINE__, (MESSAGE), ARRAYOFCONST(PARAMS))
class Callstack
{
public:
  inline Callstack(const wchar_t * File, const wchar_t * Func, unsigned int Line, const wchar_t * Message) :
    FFile(File), FFunc(Func), FLine(Line), FMessage(Message), FDepth(0)
  {
    if (IsTracing)
    {
      if (CallstackTls != CallstackTlsOff)
      {
        FDepth = reinterpret_cast<unsigned int>(TlsGetValue(CallstackTls)) + 1;
        TlsSetValue(CallstackTls, reinterpret_cast<void *>(FDepth));
      }
      TraceFmt(FFile, FFunc, FLine, L"Entry: %s [%d]", ARRAYOFCONST((FMessage, int(FDepth))));
    }
  }

  inline ~Callstack()
  {
    if (IsTracing)
    {
      if (FDepth > 0)
      {
        TlsSetValue(CallstackTls, reinterpret_cast<void *>(FDepth - 1));
      }
      TraceFmt(FFile, FFunc, FLine, L"Exit: %s [%d]", ARRAYOFCONST((FMessage, int(FDepth))));
    }
  }

private:
  const wchar_t * FFile;
  const wchar_t * FFunc;
  unsigned int FLine;
  const wchar_t * FMessage;
  unsigned int FDepth;
};
void __callstack(const wchar_t*, const wchar_t*, unsigned int, const wchar_t*) {}
#define __callstack1 __callstack
#define CCALLSTACKIMPL(TRACING, X) _TRACING_CALLSTACK TRACING X(TEXT(__FILE__), TEXT(__FUNC__), __LINE__, L"")
#else // ifdef _DEBUG
#define CTRACEIMPL(TRACING, PARAMS)
#define CTRACEFMTIMPL(TRACING, MESSAGE, PARAMS)
#define CCALLSTACKIMPL(TRACING, X)
#endif // ifdef _DEBUG

#define TRACE(MESSAGE) CTRACEIMPL(TRACING, (_T(MESSAGE)))
#define TRACEFMT(MESSAGE, PARAMS) CTRACEFMTIMPL(TRACING, _T(MESSAGE), PARAMS)
#define CTRACE(TRACING, MESSAGE) CTRACEIMPL(TRACING, _T(MESSAGE))
#define CTRACEFMT(TRACING, MESSAGE, PARAMS) CTRACEFMTIMPL(TRACING, _T(MESSAGE), PARAMS)

#define CCALLSTACK(TRACING) CCALLSTACKIMPL(TRACING, _TRACING_CALLSTACKI TRACING)
#define CCALLSTACK1(TRACING) CCALLSTACKIMPL(TRACING ,_TRACING_CALLSTACKI TRACING ## 1)
#define CALLSTACK CCALLSTACK(TRACING)
#define CALLSTACK1 CCALLSTACK1(TRACING)
//!CLEANEND
//---------------------------------------------------------------------------
#include <assert.h>
#ifndef _DEBUG
#undef assert
#define assert(p)   ((void)0)
#define CHECK(p) p
#define FAIL
#define TRACE_EXCEPT_BEGIN
#define TRACE_EXCEPT_END
#define TRACE_CATCH_ALL catch(...)
#define CLEAN_INLINE
#else
//!CLEANBEGIN
#ifndef DESIGN_ONLY
#undef assert
void __fastcall DoAssert(wchar_t * Message, wchar_t * Filename, int LineNumber);
#define assert(p) ((p) ? (void)0 : DoAssert(TEXT(#p), TEXT(__FILE__), __LINE__))
#endif // ifndef DESIGN_ONLY
//!CLEANEND
#define CHECK(p) { bool __CHECK_RESULT__ = (p); assert(__CHECK_RESULT__); }
#define FAIL assert(false)
#define TRACE_EXCEPT_BEGIN try {
#define TRACE_EXCEPT_END } catch (Exception & TraceE) { TRACEFMT("E [%s]", (TraceE.Message)); throw; }
#define TRACE_CATCH_ALL catch (Exception & TraceE)
#define TRACEE_(E) TRACEFMT(#E" [%s]", (E.Message))
#define TRACEE TRACEE_(E)
#define TRACE_EXCEPT TRACEE_(TraceE)
#define CLEAN_INLINE
#endif
#define USEDPARAM(p) ((&p) == (&p))
//---------------------------------------------------------------------------
#endif
