#include "Common.h"
#include "Log.h"
#include "ColorPairManager.h"

bool
ConfirmBox(WINDOW* parent,
           string  title,
           string  message)
{
   int      nColumns       = message.size() + 4;
   WINDOW*  confirm        = 0;
   int      option         = 0;
   int      key;

   if (nColumns < MIN_CONFIRM_COLS)
      nColumns = MIN_CONFIRM_COLS;

   else if (nColumns > MAX_CONFIRM_COLS)
      nColumns = MAX_CONFIRM_COLS;

   confirm = subwin(parent, 6, nColumns, (LINES - 6)/2, (COLS - nColumns)/2);

   if (confirm == 0)
   {
      Log::getInstance().write("Failed to intialize confirm window.");
      return false;
   }

   wclear(parent);
   wbkgd(confirm, COLOR_PAIR(ColorPairManager::getInstance().getColorPair(COLOR_WHITE, COLOR_BLUE)));
   wborder(confirm, 0, 0, 0, 0, 0, 0, 0, 0);

   mvwaddstr(confirm, 0, 5, title.c_str());
   mvwaddstr(confirm, 2, (nColumns - message.size())/2, message.c_str());
   wattron(confirm, A_REVERSE);
   mvwaddstr(confirm, 4, nColumns/2 - 6, "OK");
   wattroff(confirm, A_REVERSE);
   mvwaddstr(confirm, 4, nColumns/2, "CANCEL");
   wrefresh(confirm);

   key = wgetch(confirm);

   while (key != '\n')
   {
      if (key == KEY_LEFT && option != 0)
         option = 0;

      else if (key == KEY_RIGHT && option != 1)
         option = 1;

      else if (key == 27)
      {
         option = 1;
         break;
      }

      if (option == 0)
      {
         wattron(confirm, A_REVERSE);
         mvwaddstr(confirm, 4, nColumns/2 - 6, "OK");
         wattroff(confirm, A_REVERSE);
         mvwaddstr(confirm, 4, nColumns/2, "CANCEL");
      }
      else
      {
         wattroff(confirm, A_REVERSE);
         mvwaddstr(confirm, 4, nColumns/2 - 6, "OK");
         wattron(confirm, A_REVERSE);
         mvwaddstr(confirm, 4, nColumns/2, "CANCEL");
         wattroff(confirm, A_REVERSE);
      }

      wrefresh(confirm);
      key = wgetch(confirm);
   }

   wclear(parent);
   wrefresh(parent);
   delwin(confirm);

   if (option == 0)
      return true;

   return false;
}

void
MessageBox(WINDOW* parent,
           string  title,
           string  message)
{
   int      nColumns       = message.size() + 4;
   int      nLines         = nColumns / MAX_MESSAGEBOX_COLS + 5;
   WINDOW*  messageBox     = 0;
   WINDOW*  textArea       = 0;

   if (nColumns < MIN_MESSAGEBOX_COLS)
      nColumns = MIN_MESSAGEBOX_COLS;

   else if (nColumns > MAX_MESSAGEBOX_COLS)
      nColumns = MAX_MESSAGEBOX_COLS;

   messageBox = subwin(parent, nLines, nColumns, (LINES - nLines)/2, (COLS - nColumns)/2);

   if (messageBox == 0)
   {
      Log::getInstance().write("Failed to intialize message box window.");
      return;
   }

   textArea = subwin(messageBox, nLines - 4, nColumns - 4, (LINES - nLines)/2 + 2, (COLS - nColumns)/2 + 2);

   if (textArea == 0)
   {
      delwin(messageBox);
      Log::getInstance().write("Failed to intialize textArea window.");
      return;
   }

   nodelay(parent, false);
   nodelay(messageBox, false);
   wclear(parent);
   wbkgd(messageBox, COLOR_PAIR(ColorPairManager::getInstance().getColorPair(COLOR_WHITE, COLOR_BLUE)));
   wbkgd(textArea, COLOR_PAIR(ColorPairManager::getInstance().getColorPair(COLOR_WHITE, COLOR_BLUE)));
   wborder(messageBox, 0, 0, 0, 0, 0, 0, 0, 0);

   mvwaddstr(messageBox, 0, 5, title.c_str());
   //mvwaddstr(messageBox, 2, (nColumns - message.size())/2, message.c_str());
   waddstr(textArea, message.c_str());
   wrefresh(messageBox);

   wgetch(messageBox);

   wclear(parent);
   wrefresh(parent);
   delwin(textArea);
   delwin(messageBox);
   nodelay(parent, true);
}

std::string
StringBox(WINDOW* parent,
          string  title,
          string  message,
          int     maxLength)
{
   int         nColumns         = (message.size() > maxLength ? message.size() : maxLength) + 4;
   int         nLines           = maxLength / MAX_MESSAGEBOX_COLS + 6;
   WINDOW*     stringBox        = 0;
   WINDOW*     textArea         = 0;
   std::string result;

   if (nColumns < MIN_MESSAGEBOX_COLS)
      nColumns = MIN_MESSAGEBOX_COLS;

   else if (nColumns > MAX_MESSAGEBOX_COLS)
      nColumns = MAX_MESSAGEBOX_COLS;

   stringBox = subwin(parent, nLines, nColumns, (LINES - nLines)/2, (COLS - nColumns)/2);

   if (stringBox == 0)
   {
      Log::getInstance().write("Failed to intialize stringBox window.");
      return result;
   }

   textArea = subwin(stringBox, nLines - 4, nColumns - 4, (LINES - nLines)/2 + 4, (COLS - nColumns)/2 + 2);

   if (textArea == 0)
   {
      delwin(stringBox);
      Log::getInstance().write("Failed to intialize textArea window.");
      return result;
   }

   wclear(parent);
   wbkgd(stringBox, COLOR_PAIR(ColorPairManager::getInstance().getColorPair(COLOR_WHITE, COLOR_BLUE)));
   wborder(stringBox, 0, 0, 0, 0, 0, 0, 0, 0);

   mvwaddstr(stringBox, 0, 5, title.c_str());
   mvwaddstr(stringBox, 2, (nColumns - message.size())/2, message.c_str());

   echo();

   char buffer[maxLength + 1];
   wrefresh(stringBox);
   mvwgetnstr(textArea, 0, 0, buffer, maxLength);

   noecho();

   result = buffer;

   wclear(parent);
   wrefresh(parent);
   delwin(textArea);
   delwin(stringBox);

   return result;
}

void
PackInteger16(unsigned char* buf,
              unsigned int   i)
{
    *buf++ = i >> 8;
    *buf++ = i;
}

void
PackInteger32(unsigned char* buf,
              unsigned int   i)
{
    *buf++ = i >> 24;
    *buf++ = i >> 16;
    *buf++ = i >> 8;
    *buf++ = i;
}

void
PackInteger64(unsigned char* buf,
              uint64_t       i)
{
    *buf++ = i >> 56;
    *buf++ = i >> 48;
    *buf++ = i >> 40;
    *buf++ = i >> 32;
    *buf++ = i >> 24;
    *buf++ = i >> 16;
    *buf++ = i >> 8;
    *buf++ = i;
}

unsigned int
UnpackInteger16(unsigned char* buf)
{
    return (buf[0] << 8) | buf[1];
}

unsigned int
UnpackInteger32(unsigned char* buf)
{
    return (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
}

uint64_t
UnpackInteger64(unsigned char* buf)
{
    return (buf[0] << 56) | (buf[1] << 48) | (buf[2] << 40) | (buf[3] << 32) |
           (buf[4] << 24) | (buf[5] << 16) | (buf[6] << 8)  | buf[7];
}

long long   Pack754  (long double f, unsigned nBit, unsigned nExponentBit)
{
   long double normalizedF;
   int         nShift;

   /*
    * The structure of floating-point numbers in IEE754
    */
   long long   sign, mantissa, exponent;

   unsigned    nMantissaBit = nBit - nExponentBit - 1;

   // No need further calculation
   if (f == 0.0)
      return 0;

   /*
    * Normalize f
    */

   if (f < 0)
   {
      normalizedF = -f;
      sign = 1;
   }
   else
   {
      normalizedF = f;
      sign = 0;
   }

   nShift = 0;

   while (normalizedF >= 2.0)
   {
      normalizedF /= 2.0;
      nShift++;
   }

   while (normalizedF < 1.0)
   {
      normalizedF *= 2.0;
      nShift--;
   }

   normalizedF -= 1.0;

   /*
    * Calculate components, and voila!
    */

   mantissa = normalizedF * ((1 << nMantissaBit) + 0.5);
   exponent = nShift + ((1 << (nExponentBit - 1)) - 1);

   return sign << (nBit - 1) | exponent << nMantissaBit | mantissa;
}

long double Unpack754(long long i, unsigned nBit, unsigned nExponentBit)
{
   long double result;
   long long   shift;
   unsigned    bias;

   unsigned    nMantissaBit = nBit - nExponentBit - 1;

   if (i == 0)
      return 0.0;

   result  = (i & ((1 << nMantissaBit) - 1));
   result /= 1 << nMantissaBit;
   result += 1.0;

   bias    = (1 << (nExponentBit - 1)) - 1;
   shift   = ((i >> nMantissaBit) & ((1 << nExponentBit) - 1)) - bias;

   while (shift > 0)
   {
      result *= 2.0;
      shift--;
   }

   while (shift < 0)
   {
      result /= 2.0;
      shift++;
   }

   result *= ((i >> (nBit - 1)) & 1 ? -1.0 : 1.0);

   return result;
}
