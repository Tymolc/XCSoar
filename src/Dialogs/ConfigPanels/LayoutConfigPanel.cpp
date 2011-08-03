/*
Copyright_License {

  XCSoar Glide Computer - http://www.xcsoar.org/
  Copyright (C) 2000-2011 The XCSoar Project
  A detailed list of copyright holders can be found in the file "AUTHORS".

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
}
*/

#include "LayoutConfigPanel.hpp"
#include "Profile/ProfileKeys.hpp"
#include "Profile/Profile.hpp"
#include "Profile/DisplayConfig.hpp"
#include "Form/Edit.hpp"
#include "Form/Util.hpp"
#include "DataField/Enum.hpp"
#include "InfoBoxes/InfoBoxLayout.hpp"
#include "Hardware/Display.hpp"
#include "Interface.hpp"
#include "Appearance.hpp"
#include "MainWindow.hpp"
#include "LogFile.hpp"
#include "Screen/Graphics.hpp"
#include "Language/Language.hpp"
#include "Dialogs/XML.hpp"

static WndForm* wf = NULL;


void
LayoutConfigPanel::Init(WndForm *_wf)
{
  assert(_wf != NULL);
  wf = _wf;
  WndProperty *wp;

  if (Display::RotateSupported()) {
    wp = (WndProperty*)wf->FindByName(_T("prpDisplayOrientation"));
    assert(wp != NULL);

    DataFieldEnum *dfe = (DataFieldEnum *)wp->GetDataField();
    dfe->addEnumText(_("Default"));
    dfe->addEnumText(_("Portrait"));
    dfe->addEnumText(_("Landscape"));
    dfe->addEnumText(_("Reverse Portrait"));
    dfe->addEnumText(_("Reverse Landscape"));
    dfe->Set(Profile::GetDisplayOrientation());
    wp->RefreshDisplay();
  } else {
    wp = (WndProperty*)wf->FindByName(_T("prpDisplayOrientation"));
    assert(wp != NULL);
    wp->hide();
  }

  wp = (WndProperty*)wf->FindByName(_T("prpAppInfoBoxGeom"));
  if (wp) {
    DataFieldEnum* dfe;
    dfe = (DataFieldEnum*)wp->GetDataField();

    dfe->addEnumText(_("8 Top + Bottom (Portrait)"),
                     InfoBoxLayout::ibTop4Bottom4);
    dfe->addEnumText(_("8 Bottom (Portrait)"), InfoBoxLayout::ibBottom8);
    dfe->addEnumText(_("8 Bottom + Vario (Portrait)"), 
                    InfoBoxLayout::ibBottom8Vario);
    dfe->addEnumText(_("8 Top (Portrait)"), InfoBoxLayout::ibTop8);
    dfe->addEnumText(_("8 Left + Right (Landscape)"),
                     InfoBoxLayout::ibLeft4Right4);
    dfe->addEnumText(_("8 Left (Landscape)"), InfoBoxLayout::ibLeft8);
    dfe->addEnumText(_("8 Right (Landscape)"), InfoBoxLayout::ibRight8);
    dfe->addEnumText(_("9 Right + Vario (Landscape)"), InfoBoxLayout::ibGNav);
    dfe->addEnumText(_("9 Left + Right (Landscape)"), InfoBoxLayout::ibGNav2);
    dfe->addEnumText(_("5 Right (Square)"), InfoBoxLayout::ibSquare);
    dfe->addEnumText(_("12 Right (Landscape)"), InfoBoxLayout::ibRight12);
    dfe->addEnumText(_("12 Bottom (Portrait)"), InfoBoxLayout::ibBottom12);
    dfe->addEnumText(_("12 Top (Portrait)"), InfoBoxLayout::ibTop12);
    dfe->addEnumText(_("24 Right (Landscape)"), InfoBoxLayout::ibRight24);
    dfe->Set(InfoBoxLayout::InfoBoxGeometry);
    wp->RefreshDisplay();
  }

  wp = (WndProperty*)wf->FindByName(_T("prpAppFlarmLocation"));
  if (wp) {
    DataFieldEnum* dfe;
    dfe = (DataFieldEnum*)wp->GetDataField();
    dfe->addEnumText(_("Auto (follow infoboxes)"), flAuto);
    dfe->addEnumText(_("Top Left"), flTopLeft);
    dfe->addEnumText(_("Top Right"), flTopRight);
    dfe->addEnumText(_("Bottom Left"), flBottomLeft);
    dfe->addEnumText(_("Bottom Right"), flBottomRight);
    dfe->addEnumText(_("Centre Top"), flCentreTop);
    dfe->addEnumText(_("Centre Bottom"), flCentreBottom);
    unsigned val = 0;
    if(!Profile::Get(szProfileFlarmLocation, val)) val = 0;
    dfe->Set(val);
    wp->RefreshDisplay();
  }

  wp = (WndProperty*)wf->FindByName(_T("prpAppStatusMessageAlignment"));
  if (wp) {
    DataFieldEnum* dfe;
    dfe = (DataFieldEnum*)wp->GetDataField();
    dfe->addEnumText(_("Center"));
    dfe->addEnumText(_("Topleft"));
    dfe->Set(Appearance.StateMessageAlign);
    wp->RefreshDisplay();
  }

  wp = (WndProperty*)wf->FindByName(_T("prpDialogStyle"));
  if (wp) {
    DataFieldEnum* dfe;
    dfe = (DataFieldEnum*)wp->GetDataField();
    dfe->addEnumText(_("Full width"));
    dfe->addEnumText(_("Scaled"));
    dfe->addEnumText(_("Scaled centered"));
    dfe->addEnumText(_("Fixed"));
    dfe->Set(DialogStyleSetting);
    wp->RefreshDisplay();
  }

  LoadFormProperty(*wf, _T("prpAppInverseInfoBox"),
                   Appearance.InverseInfoBox);

  LoadFormProperty(*wf, _T("prpAppInfoBoxColors"), Appearance.InfoBoxColors);

  wp = (WndProperty*)wf->FindByName(_T("prpAppInfoBoxBorder"));
  if (wp) {
    DataFieldEnum* dfe;
    dfe = (DataFieldEnum*)wp->GetDataField();
    dfe->addEnumText(_("Box"));
    dfe->addEnumText(_("Tab"));
    dfe->Set(Appearance.InfoBoxBorder);
    wp->RefreshDisplay();
  }

  wp = (WndProperty*)wf->FindByName(_T("prpTabDialogStyle"));
  if (wp) {
    DataFieldEnum* dfe;
    dfe = (DataFieldEnum*)wp->GetDataField();
    dfe->addEnumText(_("Text"));
    dfe->addEnumText(_("Icons"));
    dfe->Set(CommonInterface::GetUISettings().dialog.tab_style);
    wp->RefreshDisplay();
  }

}


bool
LayoutConfigPanel::Save(bool &requirerestart)
{
  bool changed = false;
  WndProperty *wp;

  bool orientation_changed = false;

  if (Display::RotateSupported()) {
    wp = (WndProperty*)wf->FindByName(_T("prpDisplayOrientation"));
    assert(wp != NULL);

    const DataFieldEnum *dfe = (const DataFieldEnum *)wp->GetDataField();
    Display::orientation orientation =
      (Display::orientation)dfe->GetAsInteger();
    if (orientation != Profile::GetDisplayOrientation()) {
      Profile::SetDisplayOrientation(orientation);
      changed = true;
      orientation_changed = true;
    }
  }

  bool info_box_geometry_changed = false;

  info_box_geometry_changed |=
    SaveFormPropertyEnum(*wf, _T("prpAppInfoBoxGeom"),
                         szProfileInfoBoxGeometry,
                         InfoBoxLayout::InfoBoxGeometry);

  wp = (WndProperty*)wf->FindByName(_T("prpAppFlarmLocation"));
  if (wp) {
    unsigned newval = (unsigned)wp->GetDataField()->GetAsInteger();
    unsigned oldval = 0;
    if(!Profile::Get(szProfileFlarmLocation, oldval)) oldval = 0;
    if (newval != oldval) {
      Profile::Set(szProfileFlarmLocation, newval);
      info_box_geometry_changed = true;
    }
  }

  changed |= info_box_geometry_changed;

  changed |= SaveFormPropertyEnum(*wf, _T("prpAppStatusMessageAlignment"),
                                  szProfileAppStatusMessageAlignment,
                                  Appearance.StateMessageAlign);

  changed |= SaveFormPropertyEnum(*wf, _T("prpDialogStyle"),
                                  szProfileAppDialogStyle,
                                  DialogStyleSetting);

  changed |= requirerestart |=
    SaveFormPropertyEnum(*wf, _T("prpAppInfoBoxBorder"),
                         szProfileAppInfoBoxBorder,
                         Appearance.InfoBoxBorder);

  changed |= requirerestart |=
    SaveFormProperty(*wf, _T("prpAppInverseInfoBox"),
                     szProfileAppInverseInfoBox, Appearance.InverseInfoBox);

  changed |= requirerestart |=
    SaveFormProperty(*wf, _T("prpAppInfoBoxColors"),
                     szProfileAppInfoBoxColors, Appearance.InfoBoxColors);

  DialogSettings &dialog_settings = CommonInterface::SetUISettings().dialog;
  changed |= SaveFormPropertyEnum(*wf, _T("prpTabDialogStyle"),
                                  szProfileAppDialogTabStyle,
                                  dialog_settings.tab_style);

  if (orientation_changed) {
    assert(Display::RotateSupported());

    Display::orientation orientation = Profile::GetDisplayOrientation();
    if (orientation == Display::ORIENTATION_DEFAULT)
      Display::RotateRestore();
    else {
      if (!Display::Rotate(orientation))
        LogStartUp(_T("Display rotation failed"));
    }
  } else if (info_box_geometry_changed)
    XCSoarInterface::main_window.ReinitialiseLayout();

  return changed;
}
