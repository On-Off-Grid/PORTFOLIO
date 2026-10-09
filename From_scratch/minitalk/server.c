#include "minitalk.h"

static pid_t	g_pid = 0;

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static int	bit_count = 0;
	static char	current_char = 0;

	(void) context;
	if (g_pid != info->si_pid)
	{
		g_pid = info->si_pid;
		bit_count = 0;
		current_char = 0;
	}
	if (sig == BIT_1)
		current_char |= (1 << bit_count);
	bit_count++;
	if (bit_count == 8)
	{
		ft_putchar_fd(current_char, 1);
		current_char = 0;
		bit_count = 0;
	}
	kill(info->si_pid, BIT_1);
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	(void) av;
	if (ac != 1)
	{
		ft_putstr_fd("Usage: ./server\n", 2);
		return (1);
	}
	ft_printf("Server PID: %d\n", getpid());
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(BIT_1, &sa, NULL);
	sigaction(BIT_0, &sa, NULL);
	while (1)
		pause();
	return (0);
}
