const char* compiler =
#if defined(__clang__)
    "Clang";
    import std;
#elif (defined(__GNUC__) || defined(__GNUG__)) && !defined(__clang__)
    "GCC";
    import <iostream>;
#elif defined(_MSC_VER)
    "MSVC";
    import std;
    import std.compat;
#endif

import Game;

int main() {

    #if defined(_MSC_VER)
        printf("Import std.compat to get global names like printf()\n");
    #endif

    jod::RunGame();

    return 0;
}

