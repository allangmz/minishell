// // #include<stdio.h>
// // #include <unistd.h>
// // #include<signal.h>
// // #include <stdlib.h>

// // void handle_sigint(int sig)
// // {
// //     printf("Caught signal %d\n", sig);
// //     exit(0);
// // }

// // int main()
// // {
// //     signal(SIGINT, handle_sigint);
// //     while (1)
// //     {
// //         printf("hello world\n");
// //         sleep(1);
// //     }
// //     return 0;
// // }

// #include <signal.h>
// #include <stdio.h>
// #include <stdlib.h>

// int shouldRun = 1;

// void sighandler(int test) {
//     printf("test %d\n", test);
//     shouldRun = 0;
// }

// int main(int argc, char *argv[]) {
//     sighandler_t signal(int signum, sighandler_t handler)
//     return EXIT_SUCCESS;
// }
#include <stdio.h>
int main()
{
	float i = 3.3;
	float j = 3.7;

		printf(" %d %d\n", (int) i, (int) j);
}