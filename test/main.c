void tests_dir(void);
void tests_stash(void);
void tests_resource(void);
void tests_location(void);

int main(int argc, char *argv[])
{
  tests_dir();
  tests_stash();
  tests_resource();
  tests_location();

  return 0;
}
