Summary: Magic Linux Fcitx Control Center Modules
Summary(zh_CN.GB18030): Magic Linux Fcitx ��������ģ��
Name: kcm_fcitxconfig
Version: 1.5.1
Release: 1mgc
Group: User Interface/X
Group(zh_CN.GB18030): �û�����/X
License: GPL v2+
Source: fcitxconfig.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

URL: http://www.magiclinux.org
Distribution: Magic Linux

BuildRequires: cmake >= 2.6.0
BuildRequires: qt4-devel
BuildRequires: libkdelibs4-devel
BuildRequires: gettext
Requires: kdebase4-runtime

%description
Magic Linux Fcitx Control Center Modules.

%description -l zh_CN.GB18030
Magic Linux Fcitx ��������ģ�顣

%prep
%setup -q -n fcitxconfig

%build
mkdir build
cd build
%cmake_kde4 ..

make

%install
rm -rf %{buildroot}
cd build
make DESTDIR=%{buildroot} install

%clean
rm -rf %{buildroot} %{_builddir}/%{buildsubdir}

%files
%defattr(-,root,root,-)
%doc AUTHORS COPYING
%{kde4_plugindir}/kcm_fcitxconfig.so
%{kde4_servicesdir}/fcitxconfig.desktop
%{kde4_iconsdir}/hicolor/32x32/apps/qfcitxconfig.png
%{kde4_localedir}/zh_CN/LC_MESSAGES/kcm_fcitxconfig.mo

%changelog
* Sun Jul 26 2009 Ni Hui <shuizhuyuanluo@126.com> - 1.5.1-1mgc
- ���������ļ�ʱ������ fcitx ���̣�����ʱ���� fcitx
- ����  ���³���

* Thu Jul 2 2009 Ni Hui <shuizhuyuanluo@126.com> - 1.5-1mgc
- ��ֲ�� cmake/Qt4/KDE4
- ���ʻ�֧��
- ����  �����³�ʮ
