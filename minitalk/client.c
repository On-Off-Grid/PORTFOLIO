#include "minitalk.h"

static int		g_received = 0;
static void	check(int sig)
{
	if (sig == BIT_1)
		g_received = 1; 
}

static void send_char(pid_t server_pid, char c)
{
    int		i;
	int		signal;

    i = 0;
    while (i < 8)
    {
		if (((c >> i) & 1) == 1)
        	signal = BIT_1;
    	else
        	signal = BIT_0;
    	if (kill(server_pid, signal) == -1)
    	{
        	ft_printf("Error: Failed to send signal to PID %d\n", server_pid);
        	exit(1);
		}
		while (!g_received)
		{
			if (kill(server_pid, 0) == -1)
				exit(1);
		}
		g_received = 0;
		i++;
    }
}

int main(int argc, char **argv)
{
    pid_t server_pid;
    size_t i;
	
	signal(BIT_1, check);
    if (argc != 3)
    {
        ft_printf("Usage: %s <server_pid> <message>\n", argv[0]);
        return (1);
    }
    server_pid = ft_atoi(argv[1]);
    if (server_pid <= 0 || kill(server_pid, 0) == -1)
    {
        ft_printf("Invalid PID: %s\n", argv[1]);
        return (1);
    }
    i = 0;
    while (argv[2][i])
	{
        send_char(server_pid, argv[2][i]);
		i++;
	}
	return (0);
}
