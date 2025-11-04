const char* dir_to_string(enum dir_t d)
{
  switch (d) {
  case 0:
    return "NORTH";
  case 1:
    return "EAST";
  case 2:
    return "SOUTH";
  case 3:
    return "WEST";
  default:
    return "";
  }
}

const char* dir_to_short_string(enum dir_t d);const char* dir_to_string(enum dir_t d)
{
  switch (d) {
  case 0:
    return "N";
  case 1:
    return "E";
  case 2:
    return "S";
  case 3:
    return "W";
  default:
    return "";
  }
}

enum dir_t dir_opposite(enum dir_t d)
{
  switch (d) {
  case 0:
    return "SOUTH";
  case 1:
    return "WEST";
  case 2:
    return "NORTH";
  case 3:
    return "EAST";
  default:
    return "";
  }
}
