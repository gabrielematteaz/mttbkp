#ifndef MTTOPT_HPP
#define MTTOPT_HPP

#include <vector>

struct mttopt_opt_t
{
	char shrt;
	uint8_t flags;
	bool found;
	const char *arg;

	mttopt_opt_t() noexcept;
	mttopt_opt_t(char shrt, uint8_t flags) noexcept;
};

struct mttopt_wopt_t
{
	wchar_t wshrt;
	uint8_t flags;
	bool found;
	const wchar_t *warg;

	mttopt_wopt_t() noexcept;
	mttopt_wopt_t(wchar_t shrt, uint8_t flags) noexcept;
};

#define OPT_FLAGS_OVERWRITE_ON_COPY 0
#define OPT_FLAGS_IGNORE_COPIES 1
#define OPT_FLAGS_EXIT_ON_COPY 2
#define OPT_FLAGS_HAS_NO_ARG 0
#define OPT_FLAGS_CAN_HAVE_ARG 4
#define OPT_FLAGS_MUST_HAVE_ARG 12

using mttopt_optv_t = std::vector < mttopt_opt_t >;
using mttopt_woptv_t = std::vector < mttopt_wopt_t >;

int mttopt_extr_optv(int argc, char *argv[], mttopt_optv_t &optv) noexcept;
int mttopt_extr_woptv(int wargc, wchar_t *wargv[], mttopt_woptv_t &woptv) noexcept;

#endif