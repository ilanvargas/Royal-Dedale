#include "resource.h"

const char* resource_to_string(enum resource_t r)
{
    switch(r)
    {
        case NOTHING: 
            return "NOTHING";
        case STEP:
            return "STEP";
        case KEY:
            return "KEY";
        case GEM:
            return "GEM";
        case GOLD:
            return "GOLD";
        case SILK:
            return "SILK";
        case FUR:
            return "FUR";
        case INCENSE:
            return "INCENSE";
        case POTION:
            return "POTION";
        case OIL:
            return "OIL";
        case CRYSTAL:
            return "CRYSTAL";
        default:
            return "";
    }
}

const char* resource_to_short_string(enum resource_t r)
{
    switch(r)
    {
        case NOTHING: 
            return "N";
        case STEP:
            return "St";
        case KEY:
            return "K";
        case GEM:
            return "Gm";
        case GOLD:
            return "Gd";
        case SILK:
            return "Sk";
        case FUR:
            return "F";
        case INCENSE:
            return "I";
        case POTION:
            return "P";
        case OIL:
            return "O";
        case CRYSTAL:
            return "C";
        default:
            return "";
    }
}
