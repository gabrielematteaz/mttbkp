#include <filesystem>
#include "../mttlib/mttopt-cpp/mttopt.hpp"
#include <iostream>

namespace fs = std::filesystem;

int wmain(int wargc, wchar_t *wargv[])
{
	wchar_t **wav = wargv + 1, *warg = *wav;

	if (warg == nullptr) return 1;

	wchar_t **wavc = wargv + wargc;

	try
	{
		fs::path mttrepdir(L".mttbkp");

		if (wcscmp(warg, L"create") == 0)
		{
			mttopt_woptv_t woptv = { mttopt_wopt_t(L'f', OPT_FLAGS_MUST_HAVE_ARG), mttopt_wopt_t(L't', OPT_FLAGS_MUST_HAVE_ARG) };

			wargc--;
			wav = wav + mttopt_extr_woptv(wargc, wav, woptv);

			fs::path from, to = mttrepdir;

			if (woptv[0].found) from.append(woptv[0].warg);

			if (woptv[1].found) to.append(woptv[1].warg);

			if (fs::exists(to) == false && fs::create_directories(to) == false) return 2;

			while (wav < wavc)
			{
				warg = *wav;
				wav++;

				fs::path t(to);

				t.append(warg);

				if (fs::exists(t))
				{
					wchar_t ans;

					std::wcout << L'"' << t.filename().wstring() << L"\" already exists. Overwrite? [y]: ";
					std::wcin >> ans;

					if (ans != L'y') continue;
				}

				fs::copy(fs::path(from).append(warg), t, fs::copy_options::overwrite_existing | fs::copy_options::recursive);
			}
		}
		else if (wcscmp(warg, L"remove") == 0)
		{
			mttopt_woptv_t woptv = { mttopt_wopt_t(L'f', OPT_FLAGS_MUST_HAVE_ARG) };

			wargc--;
			wav = wav + mttopt_extr_woptv(wargc, wav, woptv);

			if (woptv[0].found) mttrepdir.append(woptv[0].warg);

			while (wav < wavc)
			{
				warg = *wav;
				fs::remove_all(fs::path(mttrepdir).append(warg));
				wav++;
			}
		}
		if (wcscmp(warg, L"restore") == 0)
		{
			mttopt_woptv_t woptv = { mttopt_wopt_t(L'f', OPT_FLAGS_MUST_HAVE_ARG), mttopt_wopt_t(L't', OPT_FLAGS_MUST_HAVE_ARG) };

			wargc--;
			wav = wav + mttopt_extr_woptv(wargc, wav, woptv);

			fs::path from = mttrepdir, to;

			if (woptv[0].found) from.append(woptv[0].warg);

			if (woptv[1].found) to.append(woptv[1].warg);

			if (fs::exists(to) == false && fs::create_directories(to) == false) return 3;

			while (wav < wavc)
			{
				warg = *wav;

				warg = *wav;

				fs::path t(to);

				t.append(warg);

				if (fs::exists(t))
				{
					wchar_t ans;

					std::wcout << L'"' << t.wstring() << L"\" already exists. Overwrite? [y]" << std::endl;
					std::wcin >> ans;

					if (ans != L'y') continue;
				}

				fs::copy(fs::path(from).append(warg), fs::path(to).append(warg), fs::copy_options::overwrite_existing | fs::copy_options::recursive);
				wav++;
			}
		}
	}
	catch(const std::exception &ex)
	{
		std::cerr << ex.what() << std::endl;
	}

	return 0;
}