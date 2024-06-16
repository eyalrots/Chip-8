
int main(int argc, char *argv[]) {
#if defined(__aarch64__) || defined(_M_ARM64)
  return 0;
#else
  choke
#endif
}

