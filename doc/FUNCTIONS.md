# FUNCTIONS ALLOWED FOR PHILOSOPHERS

The following functions are allowed to be used in the philosophers project:

- **memset**: to set memory with a constant byte
- **printf**: to print formatted output
- **malloc**: to allocate memory dynamically
- **free**: to deallocate memory
- **write**: to write data to a file descriptor

- **usleep**: to suspend execution for microsecond intervals
- **gettimeofday**: to get the current time

- **pthread_create**: to create a new thread
- **pthread_detach**: to detach a thread
- **pthread_join**: to join with a terminated thread
- **pthread_mutex_init**: to initialize a mutex
- **pthread_mutex_destroy**: to destroy a mutex
- **pthread_mutex_lock**: to lock a mutex
- **pthread_mutex_unlock**: to unlock a mutex

```c
# include <string.h>	// To use memset
# include <stdio.h>		// To use printf
# include <stdlib.h>	// To use malloc, free
# include <unistd.h>	// To use write, usleep
# include <sys/time.h>	// To use gettimeofday
# include <pthread.h>	// To use pthread_create, pthread_detach, pthread_join
						// pthread_mutex_init, pthread_mutex_destroy
						// pthread_mutex_lock, pthread_mutex_unlock

void	*memset(void *s, int c, size_t n);
int		printf(const char *format, ...);
void	*malloc(size_t size);
void	free(void *ptr);
ssize_t	write(int fd, const void *buf, size_t count);
int		usleep(useconds_t usec);
int		gettimeofday(struct timeval *tv, struct timezone *tz);
int		pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
int		pthread_detach(pthread_t thread);
int		pthread_join(pthread_t thread, void \**retval);
int		pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
int		pthread_mutex_destroy(pthread_mutex_t *mutex);
int		pthread_mutex_lock(pthread_mutex_t *mutex);
int		pthread_mutex_unlock(pthread_mutex_t *mutex);

```

# Example of usage for usleep and gettimeofday

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

int main() {
    struct timeval start, end;

    // Get the current time before sleeping
    gettimeofday(&start, NULL);

    // Sleep for 500,000 microseconds (0.5 seconds)
    usleep(500000);

    // Get the current time after sleeping
    gettimeofday(&end, NULL);

    // Calculate elapsed time in microseconds
    long elapsed = (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);
    printf("Elapsed time: %ld microseconds\n", elapsed);

    return 0;
}
```

# Example of usage for POSIX Thread functions

```c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Structure to hold thread data
typedef struct
{
    int thread_id;
    int* counter;
    pthread_mutex_t* mutex;
} ThreadData;

// Thread function
void* thread_function(void* arg)
{
    ThreadData* data = (ThreadData*)arg;

    pthread_mutex_lock(data->mutex); // Lock the mutex
    (*(data->counter))++;
    printf("Thread %d incremented counter to %d\n", data->thread_id, *(data->counter));
    pthread_mutex_unlock(data->mutex); // Unlock the mutex

    return NULL;
}

int main()
{
    pthread_t thread1, thread2;
    int counter = 0;
    pthread_mutex_t mutex;

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Create thread data for each thread
    ThreadData data1 = {1, &counter, &mutex};
    ThreadData data2 = {2, &counter, &mutex};

    // Create two threads
    pthread_create(&thread1, NULL, thread_function, &data1);
    pthread_create(&thread2, NULL, thread_function, &data2);

    // Join the threads (wait for them to finish)
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    printf("Final counter value: %d\n", counter);

    return 0;
}
```

# Man Example for POSIX Thread functions

```c
#include <ctype.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define handle_error_en(en, msg) \
	do                           \
	{                            \
		errno = en;              \
		perror(msg);             \
		exit(EXIT_FAILURE);      \
	} while (0)

#define handle_error(msg)   \
	do                      \
	{                       \
		perror(msg);        \
		exit(EXIT_FAILURE); \
	} while (0)

struct		thread_info
{                        /* Used as argument to thread_start() */
	pthread_t thread_id; /* ID returned by pthread_create() */
	int thread_num;      /* Application-defined thread # */
	char *argv_string;   /* From command-line argument */
};

/* Thread start function: display address near top of our stack,
   and return upper-cased copy of argv_string */

static void	*thread_start(void *arg)
{
	struct thread_info	*tinfo;
	char				*uargv;

	tinfo = arg;
	printf("Thread %d: top of stack near %p; argv_string=%s\n", tinfo->thread_num, &p, tinfo->argv_string);
	uargv = strdup(tinfo->argv_string);
	if (uargv == NULL)
		handle_error("strdup");
	for (char *p = uargv; *p != '\0'; p++)
		*p = toupper(*p);
	return (uargv);
}

int	main(int argc, char *argv[])
{
	pthread_attr_t		attr;
	size_t				stack_size;
	void				*res;
	struct thread_info	*tinfo;

	int s, opt, num_threads;
	/* The "-s" option specifies a stack size for our threads */
	stack_size = -1;
	while ((opt = getopt(argc, argv, "s:")) != -1)
	{
		switch (opt)
		{
			case 's':
				stack_size = strtoul(optarg, NULL, 0);
				break ;
			default:
				fprintf(stderr, "Usage: %s [-s stack-size] arg...\n", argv[0]);
				exit(EXIT_FAILURE);
		}
	}
	num_threads = argc - optind;
	/* Initialize thread creation attributes */
	s = pthread_attr_init(&attr);
	if (s != 0)
		handle_error_en(s, "pthread_attr_init");
	if (stack_size > 0)
	{
		s = pthread_attr_setstacksize(&attr, stack_size);
		if (s != 0)
			handle_error_en(s, "pthread_attr_setstacksize");
	}
	/* Allocate memory for pthread_create() arguments */
	tinfo = calloc(num_threads, sizeof(*tinfo));
	if (tinfo == NULL)
		handle_error("calloc");
	/* Create one thread for each command-line argument */
	for (int tnum = 0; tnum < num_threads; tnum++)
	{
		tinfo[tnum].thread_num = tnum + 1;
		tinfo[tnum].argv_string = argv[optind + tnum];
		/* The pthread_create() call stores the thread ID into corresponding element of tinfo[] */
		s = pthread_create(&tinfo[tnum].thread_id, &attr, &thread_start,
				&tinfo[tnum]);
		if (s != 0)
			handle_error_en(s, "pthread_create");
	}
	/* Destroy the thread attributes object, since it is nolonger needed */
	s = pthread_attr_destroy(&attr);
	if (s != 0)
		handle_error_en(s, "pthread_attr_destroy");
	/* Now join with each thread, and display its returned value */
	for (int tnum = 0; tnum < num_threads; tnum++)
	{
		s = pthread_join(tinfo[tnum].thread_id, &res);
		if (s != 0)
			handle_error_en(s, "pthread_join");
		printf("Joined with thread %d; returned value was %s\n",
			tinfo[tnum].thread_num, (char *)res);
		free(res); /* Free memory allocated by thread */
	}
	free(tinfo);
	exit(EXIT_SUCCESS);
}
```

# Example for POSIX Thread Create and Join functions

```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void	*thread(void *arg)
{
	char	*ret;

	printf("thread() entered with argument '%s'\n", (char *)arg);
	if ((ret = (char *)malloc(20)) == NULL)
	{
		perror("malloc() error");
		exit(2);
	}
	strcpy(ret, "This is a test");
	pthread_exit(ret);
}

int	main(void)
{
	pthread_t	thid;
	void		*ret;

	if (pthread_create(&thid, NULL, thread, "thread 1") != 0)
	{
		perror("pthread_create() error");
		exit(1);
	}
	if (pthread_join(thid, &ret) != 0)
	{
		perror("pthread_create() error");
		exit(3);
	}
	printf("thread exited with '%s'\n", (char *)ret);
}
```

