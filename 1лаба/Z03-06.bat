@echo off
if "%*" == "" (goto null) else (goto notnull)

:null
echo  ������ ����������:
echo  �����: %1
echo  ��� �����: %2
echo  + %~n0 ����� ����
echo  ++ ����� = {�������, �������}
echo  ++ ���� = ��� �����
goto exit

:notnull
if not "%2" == "" goto file else goto nofile

:nofile
echo  ������ ����������: %*
echo  �����: %1
echo  ��� �����: %2
echo  + �� ������ ��� �����
goto exit

:file
if "%1" == "�������" goto create
if "%1" == "�������" goto delete else goto failmode

:failmode
echo  ������ ����������: %*
echo  �����: %1
echo  ��� �����: %2
echo  + ����� ����� �����������
goto exit

:create
if exist %2 goto foundfile else goto createfile
goto createfile

:delete
if exist %2 goto deletefile else goto notfoundfile

:notfoundfile
echo  ������ ����������: %*
echo  �����: %1
echo  ��� �����: %2
echo  + ���� %2 �� ������
goto exit

:foundfile
echo  ������ ����������: %*
echo  �����: %1
echo  ��� �����: %2
echo  + ���� %2 ��� ����
goto exit

:createfile
copy /b NUL %2
echo  ������ ����������: %*
echo  �����: %1
echo  ��� �����: %2
echo  + ���� %2 ������
goto exit

:deletefile
del %2
echo  ������ ����������: %*
echo  �����: %1
echo  ��� �����: %2
echo  + ���� %2 ������
goto exit

:exit