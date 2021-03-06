; Script generated by the HM NIS Edit Script Wizard.

; HM NIS Edit Wizard helper defines
!define PRODUCT_NAME "Pandas vs. Mayas!"
!define PRODUCT_VERSION "1.0"
!define PRODUCT_PUBLISHER "Seed Team"
!define PRODUCT_WEB_SITE "http://www.seedframework.org/"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\pvm.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

SetCompressor bzip2

; MUI 1.67 compatible ------
!include "MUI.nsh"

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
!insertmacro MUI_PAGE_LICENSE "license.txt"
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!define MUI_FINISHPAGE_RUN "$INSTDIR\pvm.exe"
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "English"

; Reserve files
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS

; MUI end ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "Setup.exe"
InstallDir "$PROGRAMFILES\Pandas vs. Mayas"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show

Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  SetOverwrite try
  File "..\workdir\alut.dll"
  SetOutPath "$INSTDIR\data"
  File "..\workdir\data\filelist.data"
  SetOutPath "$INSTDIR\data\hud"
  File "..\workdir\data\hud\baby.sprite"
  File "..\workdir\data\hud\bg.png"
  File "..\workdir\data\hud\bg.sprite"
  File "..\workdir\data\hud\credits.png"
  File "..\workdir\data\hud\credits.sprite"
  File "..\workdir\data\hud\creditsbg.sprite"
  File "..\workdir\data\hud\gameover_love.png"
  File "..\workdir\data\hud\gameover_maia.png"
  File "..\workdir\data\hud\gameover_panda.png"
  File "..\workdir\data\hud\gameover_panda.sprite"
  File "..\workdir\data\hud\gauge.sprite"
  File "..\workdir\data\hud\menu.png"
  File "..\workdir\data\hud\menu.sprite"
  File "..\workdir\data\hud\start.sprite"
  File "..\workdir\data\hud\thanks.png"
  File "..\workdir\data\hud\thanks.sprite"
  File "..\workdir\data\hud\tutorial.png"
  File "..\workdir\data\hud\tutorial.sprite"
  SetOutPath "$INSTDIR\data"
  File "..\workdir\data\lv1.map"
  File "..\workdir\data\lv2.map"
  File "..\workdir\data\lv3.map"
  File "..\workdir\data\lv4.map"
  File "..\workdir\data\lv5.map"
  SetOutPath "$INSTDIR\data\maia"
  File "..\workdir\data\maia\maia.sprite"
  SetOutPath "$INSTDIR\data\panda"
  File "..\workdir\data\panda\panda.sprite"
  SetOutPath "$INSTDIR\data\powerups"
  File "..\workdir\data\powerups\bigorna.sprite"
  SetOutPath "$INSTDIR\data"
  File "..\workdir\data\powerup_babyshield.sprite"
  File "..\workdir\data\powerup_icons.sprite"
  File "..\workdir\data\powerup_immolation.sprite"
  File "..\workdir\data\powerup_shield.sprite"
  File "..\workdir\data\pvm0.png"
  SetOutPath "$INSTDIR\data\sound"
  File "..\workdir\data\sound\bear.sound"
  File "..\workdir\data\sound\hit.sound"
  File "..\workdir\data\sound\jetpack.sound"
  File "..\workdir\data\sound\jetpack_fail.sound"
  File "..\workdir\data\sound\maia.sound"
  File "..\workdir\data\sound\music.music"
  File "..\workdir\data\sound\powerup_01.sound"
  File "..\workdir\data\sound\powerup_02.sound"
  File "..\workdir\data\sound\powerup_03.sound"
  File "..\workdir\data\sound\powerup_04.sound"
  File "..\workdir\data\sound\start_fight.sound"
  File "..\workdir\data\sound\steps.sound"
  File "..\workdir\data\sound\wings.sound"
  File "..\workdir\data\sound\wings_fail.sound"
  SetOutPath "$INSTDIR\data\sounds"
  File "..\workdir\data\sounds\bear.ogg"
  File "..\workdir\data\sounds\GlobalGameJam02_196kbps.ogg"
  File "..\workdir\data\sounds\hit.ogg"
  File "..\workdir\data\sounds\jetpack.ogg"
  File "..\workdir\data\sounds\jetpack_fail.ogg"
  File "..\workdir\data\sounds\maia.ogg"
  File "..\workdir\data\sounds\powerup_01.ogg"
  File "..\workdir\data\sounds\powerup_02.ogg"
  File "..\workdir\data\sounds\powerup_03.ogg"
  File "..\workdir\data\sounds\powerup_04.ogg"
  File "..\workdir\data\sounds\start_fight.ogg"
  File "..\workdir\data\sounds\steps.ogg"
  File "..\workdir\data\sounds\wings.ogg"
  File "..\workdir\data\sounds\wings_fail.ogg"
  SetOutPath "$INSTDIR\data"
  File "..\workdir\data\strlist.data"
  SetOutPath "$INSTDIR\data\tileset"
  File "..\workdir\data\tileset\tileset01.png"
  SetOutPath "$INSTDIR\data"
  File "..\workdir\data\tileset_tileset01.sprite"
  SetOutPath "$INSTDIR"
  File "..\workdir\jpeg.dll"
  File "..\workdir\libpng12-0.dll"
  File "..\workdir\libtiff-3.dll"
  File "..\workdir\ogg.dll"
  File "..\workdir\OpenAL32.dll"
  File "..\workdir\pvm.exe"
  CreateDirectory "$SMPROGRAMS\Pandas vs. Mayas!"
  CreateShortCut "$SMPROGRAMS\Pandas vs. Mayas!\Pandas vs. Mayas!.lnk" "$INSTDIR\pvm.exe"
  CreateShortCut "$DESKTOP\Pandas vs. Mayas!.lnk" "$INSTDIR\pvm.exe"
  File "..\workdir\SDL.dll"
  File "..\workdir\SDL_image.dll"
  File "..\workdir\Seed.dll"
  File "..\workdir\vorbis.dll"
  File "..\workdir\vorbisfile.dll"
  File "..\workdir\wrap_oal.dll"
  File "..\workdir\zlib1.dll"
SectionEnd

Section -AdditionalIcons
  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateShortCut "$SMPROGRAMS\Pandas vs. Mayas!\Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
  CreateShortCut "$SMPROGRAMS\Pandas vs. Mayas!\Uninstall.lnk" "$INSTDIR\uninst.exe"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\pvm.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\pvm.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd


Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) was successfully removed from your computer."
FunctionEnd

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Are you sure you want to completely remove $(^Name) and all of its components?" IDYES +2
  Abort
FunctionEnd

Section Uninstall
  Delete "$INSTDIR\${PRODUCT_NAME}.url"
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\zlib1.dll"
  Delete "$INSTDIR\wrap_oal.dll"
  Delete "$INSTDIR\vorbisfile.dll"
  Delete "$INSTDIR\vorbis.dll"
  Delete "$INSTDIR\Seed.dll"
  Delete "$INSTDIR\SDL_image.dll"
  Delete "$INSTDIR\SDL.dll"
  Delete "$INSTDIR\pvm.exe"
  Delete "$INSTDIR\OpenAL32.dll"
  Delete "$INSTDIR\ogg.dll"
  Delete "$INSTDIR\libtiff-3.dll"
  Delete "$INSTDIR\libpng12-0.dll"
  Delete "$INSTDIR\jpeg.dll"
  Delete "$INSTDIR\data\tileset_tileset01.sprite"
  Delete "$INSTDIR\data\tileset\tileset01.png"
  Delete "$INSTDIR\data\strlist.data"
  Delete "$INSTDIR\data\sounds\wings_fail.ogg"
  Delete "$INSTDIR\data\sounds\wings.ogg"
  Delete "$INSTDIR\data\sounds\steps.ogg"
  Delete "$INSTDIR\data\sounds\start_fight.ogg"
  Delete "$INSTDIR\data\sounds\powerup_04.ogg"
  Delete "$INSTDIR\data\sounds\powerup_03.ogg"
  Delete "$INSTDIR\data\sounds\powerup_02.ogg"
  Delete "$INSTDIR\data\sounds\powerup_01.ogg"
  Delete "$INSTDIR\data\sounds\maia.ogg"
  Delete "$INSTDIR\data\sounds\jetpack_fail.ogg"
  Delete "$INSTDIR\data\sounds\jetpack.ogg"
  Delete "$INSTDIR\data\sounds\hit.ogg"
  Delete "$INSTDIR\data\sounds\GlobalGameJam02_196kbps.ogg"
  Delete "$INSTDIR\data\sounds\bear.ogg"
  Delete "$INSTDIR\data\sound\wings_fail.sound"
  Delete "$INSTDIR\data\sound\wings.sound"
  Delete "$INSTDIR\data\sound\steps.sound"
  Delete "$INSTDIR\data\sound\start_fight.sound"
  Delete "$INSTDIR\data\sound\powerup_04.sound"
  Delete "$INSTDIR\data\sound\powerup_03.sound"
  Delete "$INSTDIR\data\sound\powerup_02.sound"
  Delete "$INSTDIR\data\sound\powerup_01.sound"
  Delete "$INSTDIR\data\sound\music.music"
  Delete "$INSTDIR\data\sound\maia.sound"
  Delete "$INSTDIR\data\sound\jetpack_fail.sound"
  Delete "$INSTDIR\data\sound\jetpack.sound"
  Delete "$INSTDIR\data\sound\hit.sound"
  Delete "$INSTDIR\data\sound\bear.sound"
  Delete "$INSTDIR\data\pvm0.png"
  Delete "$INSTDIR\data\powerup_shield.sprite"
  Delete "$INSTDIR\data\powerup_immolation.sprite"
  Delete "$INSTDIR\data\powerup_icons.sprite"
  Delete "$INSTDIR\data\powerup_babyshield.sprite"
  Delete "$INSTDIR\data\powerups\bigorna.sprite"
  Delete "$INSTDIR\data\panda\panda.sprite"
  Delete "$INSTDIR\data\maia\maia.sprite"
  Delete "$INSTDIR\data\lv5.map"
  Delete "$INSTDIR\data\lv4.map"
  Delete "$INSTDIR\data\lv3.map"
  Delete "$INSTDIR\data\lv2.map"
  Delete "$INSTDIR\data\lv1.map"
  Delete "$INSTDIR\data\hud\tutorial.sprite"
  Delete "$INSTDIR\data\hud\tutorial.png"
  Delete "$INSTDIR\data\hud\thanks.sprite"
  Delete "$INSTDIR\data\hud\thanks.png"
  Delete "$INSTDIR\data\hud\start.sprite"
  Delete "$INSTDIR\data\hud\menu.sprite"
  Delete "$INSTDIR\data\hud\menu.png"
  Delete "$INSTDIR\data\hud\gauge.sprite"
  Delete "$INSTDIR\data\hud\gameover_panda.sprite"
  Delete "$INSTDIR\data\hud\gameover_panda.png"
  Delete "$INSTDIR\data\hud\gameover_maia.png"
  Delete "$INSTDIR\data\hud\gameover_love.png"
  Delete "$INSTDIR\data\hud\creditsbg.sprite"
  Delete "$INSTDIR\data\hud\credits.sprite"
  Delete "$INSTDIR\data\hud\credits.png"
  Delete "$INSTDIR\data\hud\bg.sprite"
  Delete "$INSTDIR\data\hud\bg.png"
  Delete "$INSTDIR\data\hud\baby.sprite"
  Delete "$INSTDIR\data\filelist.data"
  Delete "$INSTDIR\alut.dll"

  Delete "$SMPROGRAMS\Pandas vs. Mayas!\Uninstall.lnk"
  Delete "$SMPROGRAMS\Pandas vs. Mayas!\Website.lnk"
  Delete "$DESKTOP\Pandas vs. Mayas!.lnk"
  Delete "$SMPROGRAMS\Pandas vs. Mayas!\Pandas vs. Mayas!.lnk"

  RMDir "$SMPROGRAMS\Pandas vs. Mayas!"
  RMDir "$INSTDIR\data\tileset"
  RMDir "$INSTDIR\data\sounds"
  RMDir "$INSTDIR\data\sound"
  RMDir "$INSTDIR\data\powerups"
  RMDir "$INSTDIR\data\panda"
  RMDir "$INSTDIR\data\maia"
  RMDir "$INSTDIR\data\hud"
  RMDir "$INSTDIR\data"
  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd