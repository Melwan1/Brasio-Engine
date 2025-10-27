#pragma once

#define FG_ESC(seq) ("\033[38;5;" #seq "m")
#define BG_ESC(seq) ("\033[48;5;" #seq "m")

#define ESC_RESET "\033[0m"
