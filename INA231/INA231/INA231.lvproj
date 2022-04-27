<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="11008008">
	<Item Name="My Computer" Type="My Computer">
		<Property Name="NI.SortType" Type="Int">3</Property>
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="Config_Files" Type="Folder" URL="../Config_Files">
			<Property Name="NI.DISK" Type="Bool">true</Property>
		</Item>
		<Item Name="Help" Type="Folder" URL="../Help">
			<Property Name="NI.DISK" Type="Bool">true</Property>
		</Item>
		<Item Name="DIG_DAQ Commands" Type="Folder" URL="../../Shell Resources/DIG_DAQ Commands">
			<Property Name="NI.DISK" Type="Bool">true</Property>
		</Item>
		<Item Name="General VIs" Type="Folder" URL="../../Shell Resources/General VIs">
			<Property Name="NI.DISK" Type="Bool">true</Property>
		</Item>
		<Item Name="l_pse_dll" Type="Folder" URL="../../Shell Resources/l_pse_dll">
			<Property Name="NI.DISK" Type="Bool">true</Property>
		</Item>
		<Item Name="l_pse_vi" Type="Folder" URL="../../Shell Resources/l_pse_vi">
			<Property Name="NI.DISK" Type="Bool">true</Property>
		</Item>
		<Item Name="Shell VIs_DO NOT EDIT" Type="Folder" URL="../../Shell Resources/Shell VIs_DO NOT EDIT">
			<Property Name="NI.DISK" Type="Bool">true</Property>
		</Item>
		<Item Name="SM_DIG Commands" Type="Folder" URL="../../Shell Resources/SM_DIG Commands">
			<Property Name="NI.DISK" Type="Bool">true</Property>
		</Item>
		<Item Name="Output Data" Type="Folder"/>
		<Item Name="main_INA231.vi" Type="VI" URL="../main_INA231.vi"/>
		<Item Name="shell_menu.rtm" Type="Document" URL="../shell_menu.rtm"/>
		<Item Name="Help_w_Reg.vi" Type="VI" URL="../Help_w_Reg.vi"/>
		<Item Name="Write_Single_Reg.vi" Type="VI" URL="../Write_Single_Reg.vi"/>
		<Item Name="Write_All_Reg.vi" Type="VI" URL="../Write_All_Reg.vi"/>
		<Item Name="TI.ico" Type="Document" URL="../TI.ico"/>
		<Item Name="Read_All_Reg.vi" Type="VI" URL="../Read_All_Reg.vi"/>
		<Item Name="Read_Single_Reg.vi" Type="VI" URL="../Read_Single_Reg.vi"/>
		<Item Name="Global Variables.vi" Type="VI" URL="../Global Variables.vi"/>
		<Item Name="Change Log.doc" Type="Document" URL="../Change Log.doc"/>
		<Item Name="CommonPublicLicense1.rtf" Type="Document" URL="../CommonPublicLicense1.rtf"/>
		<Item Name="INA231_Read_me.rtf" Type="Document" URL="../INA231_Read_me.rtf"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="Check if File or Folder Exists.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/libraryn.llb/Check if File or Folder Exists.vi"/>
				<Item Name="NI_FileType.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/lvfile.llb/NI_FileType.lvlib"/>
				<Item Name="Error Cluster From Error Code.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Cluster From Error Code.vi"/>
				<Item Name="whitespace.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/whitespace.ctl"/>
				<Item Name="Trim Whitespace.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Trim Whitespace.vi"/>
				<Item Name="General Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/General Error Handler.vi"/>
				<Item Name="DialogType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogType.ctl"/>
				<Item Name="DialogTypeEnum.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogTypeEnum.ctl"/>
				<Item Name="General Error Handler CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/General Error Handler CORE.vi"/>
				<Item Name="Check Special Tags.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Check Special Tags.vi"/>
				<Item Name="TagReturnType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/TagReturnType.ctl"/>
				<Item Name="Set String Value.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set String Value.vi"/>
				<Item Name="GetRTHostConnectedProp.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/GetRTHostConnectedProp.vi"/>
				<Item Name="Error Code Database.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Code Database.vi"/>
				<Item Name="Format Message String.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Format Message String.vi"/>
				<Item Name="Find Tag.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Find Tag.vi"/>
				<Item Name="Search and Replace Pattern.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Search and Replace Pattern.vi"/>
				<Item Name="Set Bold Text.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set Bold Text.vi"/>
				<Item Name="Details Display Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Details Display Dialog.vi"/>
				<Item Name="ErrWarn.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/ErrWarn.ctl"/>
				<Item Name="Clear Errors.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Clear Errors.vi"/>
				<Item Name="eventvkey.ctl" Type="VI" URL="/&lt;vilib&gt;/event_ctls.llb/eventvkey.ctl"/>
				<Item Name="Not Found Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Not Found Dialog.vi"/>
				<Item Name="Three Button Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog.vi"/>
				<Item Name="Three Button Dialog CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog CORE.vi"/>
				<Item Name="Longest Line Length in Pixels.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Longest Line Length in Pixels.vi"/>
				<Item Name="Convert property node font to graphics font.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Convert property node font to graphics font.vi"/>
				<Item Name="Get Text Rect.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Get Text Rect.vi"/>
				<Item Name="BuildHelpPath.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/BuildHelpPath.vi"/>
				<Item Name="GetHelpDir.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/GetHelpDir.vi"/>
				<Item Name="Get File Extension.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/libraryn.llb/Get File Extension.vi"/>
				<Item Name="Space Constant.vi" Type="VI" URL="/&lt;vilib&gt;/dlg_ctls.llb/Space Constant.vi"/>
				<Item Name="subFile Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/express/express input/FileDialogBlock.llb/subFile Dialog.vi"/>
				<Item Name="ex_CorrectErrorChain.vi" Type="VI" URL="/&lt;vilib&gt;/express/express shared/ex_CorrectErrorChain.vi"/>
				<Item Name="System Exec.vi" Type="VI" URL="/&lt;vilib&gt;/Platform/system.llb/System Exec.vi"/>
				<Item Name="Simple Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Simple Error Handler.vi"/>
				<Item Name="NI_PackedLibraryUtility.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/LVLibp/NI_PackedLibraryUtility.lvlib"/>
				<Item Name="NI_LVConfig.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/config.llb/NI_LVConfig.lvlib"/>
				<Item Name="8.6CompatibleGlobalVar.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/config.llb/8.6CompatibleGlobalVar.vi"/>
				<Item Name="Get String Text Bounds.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Get String Text Bounds.vi"/>
				<Item Name="LVBoundsTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVBoundsTypeDef.ctl"/>
				<Item Name="Read From Spreadsheet File.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Read From Spreadsheet File.vi"/>
				<Item Name="Read From Spreadsheet File (DBL).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Read From Spreadsheet File (DBL).vi"/>
				<Item Name="Read Lines From File.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Read Lines From File.vi"/>
				<Item Name="Open File+.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Open File+.vi"/>
				<Item Name="Read File+ (string).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Read File+ (string).vi"/>
				<Item Name="compatReadText.vi" Type="VI" URL="/&lt;vilib&gt;/_oldvers/_oldvers.llb/compatReadText.vi"/>
				<Item Name="Close File+.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Close File+.vi"/>
				<Item Name="Find First Error.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Find First Error.vi"/>
				<Item Name="Read From Spreadsheet File (I64).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Read From Spreadsheet File (I64).vi"/>
				<Item Name="Read From Spreadsheet File (string).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Read From Spreadsheet File (string).vi"/>
				<Item Name="subElapsedTime.vi" Type="VI" URL="/&lt;vilib&gt;/express/express execution control/ElapsedTimeBlock.llb/subElapsedTime.vi"/>
				<Item Name="FormatTime String.vi" Type="VI" URL="/&lt;vilib&gt;/express/express execution control/ElapsedTimeBlock.llb/FormatTime String.vi"/>
				<Item Name="Write To Spreadsheet File.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Write To Spreadsheet File.vi"/>
				<Item Name="Write To Spreadsheet File (DBL).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Write To Spreadsheet File (DBL).vi"/>
				<Item Name="Write Spreadsheet String.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Write Spreadsheet String.vi"/>
				<Item Name="Write To Spreadsheet File (I64).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Write To Spreadsheet File (I64).vi"/>
				<Item Name="Write To Spreadsheet File (string).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Write To Spreadsheet File (string).vi"/>
			</Item>
			<Item Name="Global 1.vi" Type="VI" URL="../Global 1.vi"/>
		</Item>
		<Item Name="Build Specifications" Type="Build">
			<Property Name="NI.SortType" Type="Int">0</Property>
			<Item Name="INA231" Type="EXE">
				<Property Name="App_copyErrors" Type="Bool">true</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{AD4F1E5E-2D82-494A-8216-286A4AEA4AAA}</Property>
				<Property Name="App_INI_GUID" Type="Str">{5A4965C9-3161-498D-97ED-CC18C8B76CCC}</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{D1CD42C3-C212-4AD1-85E8-740413ED375C}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">INA231</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../builds/NI_AB_PROJECTNAME/INA231</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToCommon</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{06E54CDD-1D75-4E58-98E0-6AEBB572AFAD}</Property>
				<Property Name="Destination[0].destName" Type="Str">INA231.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../builds/NI_AB_PROJECTNAME/INA231/INA231.exe</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../builds/NI_AB_PROJECTNAME/INA231/data</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Exe_iconItemID" Type="Ref">/My Computer/TI.ico</Property>
				<Property Name="Source[0].itemID" Type="Str">{5387FAD9-D3C5-4CD7-BDB4-6EE140AB9077}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/main_INA231.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="Source[2].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[2].itemID" Type="Ref">/My Computer/l_pse_dll/Tio32.dll</Property>
				<Property Name="Source[2].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[3].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[3].itemID" Type="Ref">/My Computer/l_pse_dll/tio32.ini</Property>
				<Property Name="Source[3].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[4].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[4].itemID" Type="Ref">/My Computer/l_pse_dll/Tio32_20080403.dll</Property>
				<Property Name="SourceCount" Type="Int">5</Property>
				<Property Name="TgtF_autoIncrement" Type="Bool">true</Property>
				<Property Name="TgtF_companyName" Type="Str">Texas Instruments</Property>
				<Property Name="TgtF_fileDescription" Type="Str">INA231EVM Software</Property>
				<Property Name="TgtF_fileVersion.build" Type="Int">7</Property>
				<Property Name="TgtF_fileVersion.major" Type="Int">1</Property>
				<Property Name="TgtF_internalName" Type="Str">INA231</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">Texas Instruments © 2012 </Property>
				<Property Name="TgtF_productName" Type="Str">INA231</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{0A31C3C2-9203-49D1-8184-E73B9726B4B1}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">INA231.exe</Property>
			</Item>
			<Item Name="INA231 EVM" Type="Installer">
				<Property Name="Destination[0].name" Type="Str">INA231</Property>
				<Property Name="Destination[0].parent" Type="Str">{3912416A-D2E5-411B-AFEE-B63654D690C0}</Property>
				<Property Name="Destination[0].tag" Type="Str">{248B060C-ADBA-4FF6-8C35-E8DE64C81AD5}</Property>
				<Property Name="Destination[0].type" Type="Str">userFolder</Property>
				<Property Name="DestinationCount" Type="Int">1</Property>
				<Property Name="DistPart[0].flavorID" Type="Str">DefaultFull</Property>
				<Property Name="DistPart[0].productID" Type="Str">{066F687E-1CA0-4D94-A2C9-F8E6E817F4CB}</Property>
				<Property Name="DistPart[0].productName" Type="Str">NI LabVIEW Run-Time Engine 2011</Property>
				<Property Name="DistPart[0].upgradeCode" Type="Str">{6AD6C111-233B-4924-A3BF-E4813FE23C7A}</Property>
				<Property Name="DistPartCount" Type="Int">1</Property>
				<Property Name="INST_autoIncrement" Type="Bool">true</Property>
				<Property Name="INST_buildLocation" Type="Path">../builds/INA231/INA231 EVM</Property>
				<Property Name="INST_buildLocation.type" Type="Str">relativeToCommon</Property>
				<Property Name="INST_buildSpecName" Type="Str">INA231 EVM</Property>
				<Property Name="INST_defaultDir" Type="Str">{248B060C-ADBA-4FF6-8C35-E8DE64C81AD5}</Property>
				<Property Name="INST_productName" Type="Str">INA231</Property>
				<Property Name="INST_productVersion" Type="Str">1.0.4</Property>
				<Property Name="INST_readmeID" Type="Ref">/My Computer/INA231_Read_me.rtf</Property>
				<Property Name="InstSpecBitness" Type="Str">32-bit</Property>
				<Property Name="InstSpecVersion" Type="Str">11008029</Property>
				<Property Name="MSI_arpCompany" Type="Str">Texas Instruments </Property>
				<Property Name="MSI_arpURL" Type="Str">www.ti.com</Property>
				<Property Name="MSI_distID" Type="Str">{95366F24-3136-4663-A299-1540D3860EC3}</Property>
				<Property Name="MSI_licenseID" Type="Ref">/My Computer/CommonPublicLicense1.rtf</Property>
				<Property Name="MSI_osCheck" Type="Int">0</Property>
				<Property Name="MSI_upgradeCode" Type="Str">{4A8CED16-B4ED-4A34-8255-819053E7039C}</Property>
				<Property Name="MSI_windowMessage" Type="Str">Welcome to the INA231 installer</Property>
				<Property Name="MSI_windowTitle" Type="Str">INA231 EVM Software</Property>
				<Property Name="RegDest[0].dirName" Type="Str">Software</Property>
				<Property Name="RegDest[0].dirTag" Type="Str">{DDFAFC8B-E728-4AC8-96DE-B920EBB97A86}</Property>
				<Property Name="RegDest[0].parentTag" Type="Str">2</Property>
				<Property Name="RegDestCount" Type="Int">1</Property>
				<Property Name="Source[0].dest" Type="Str">{248B060C-ADBA-4FF6-8C35-E8DE64C81AD5}</Property>
				<Property Name="Source[0].File[0].dest" Type="Str">{248B060C-ADBA-4FF6-8C35-E8DE64C81AD5}</Property>
				<Property Name="Source[0].File[0].name" Type="Str">INA231.exe</Property>
				<Property Name="Source[0].File[0].Shortcut[0].destIndex" Type="Int">0</Property>
				<Property Name="Source[0].File[0].Shortcut[0].name" Type="Str">INA231</Property>
				<Property Name="Source[0].File[0].Shortcut[0].subDir" Type="Str">INA231</Property>
				<Property Name="Source[0].File[0].ShortcutCount" Type="Int">1</Property>
				<Property Name="Source[0].File[0].tag" Type="Str">{0A31C3C2-9203-49D1-8184-E73B9726B4B1}</Property>
				<Property Name="Source[0].FileCount" Type="Int">1</Property>
				<Property Name="Source[0].name" Type="Str">INA231</Property>
				<Property Name="Source[0].tag" Type="Ref">/My Computer/Build Specifications/INA231</Property>
				<Property Name="Source[0].type" Type="Str">EXE</Property>
				<Property Name="Source[1].dest" Type="Str">{248B060C-ADBA-4FF6-8C35-E8DE64C81AD5}</Property>
				<Property Name="Source[1].File[0].dest" Type="Str">{248B060C-ADBA-4FF6-8C35-E8DE64C81AD5}</Property>
				<Property Name="Source[1].File[0].name" Type="Str">Bit_Config_16b.csv</Property>
				<Property Name="Source[1].File[0].tag" Type="Ref">/My Computer/Config_Files/Bit_Config_16b.csv</Property>
				<Property Name="Source[1].FileCount" Type="Int">1</Property>
				<Property Name="Source[1].name" Type="Str">Config_Files</Property>
				<Property Name="Source[1].tag" Type="Ref">/My Computer/Config_Files</Property>
				<Property Name="Source[1].type" Type="Str">Folder</Property>
				<Property Name="Source[2].dest" Type="Str">{248B060C-ADBA-4FF6-8C35-E8DE64C81AD5}</Property>
				<Property Name="Source[2].File[0].dest" Type="Str">{248B060C-ADBA-4FF6-8C35-E8DE64C81AD5}</Property>
				<Property Name="Source[2].File[0].name" Type="Str">Reg0.rtf</Property>
				<Property Name="Source[2].File[0].tag" Type="Ref">/My Computer/Help/Reg0.rtf</Property>
				<Property Name="Source[2].FileCount" Type="Int">1</Property>
				<Property Name="Source[2].name" Type="Str">Help</Property>
				<Property Name="Source[2].tag" Type="Ref">/My Computer/Help</Property>
				<Property Name="Source[2].type" Type="Str">Folder</Property>
				<Property Name="SourceCount" Type="Int">3</Property>
			</Item>
			<Item Name="INA231-SFT-sourcecode_rev1" Type="Zip File">
				<Property Name="Absolute[0]" Type="Bool">false</Property>
				<Property Name="BuildName" Type="Str">INA231-SFT-sourcecode_rev1</Property>
				<Property Name="Comments" Type="Str"></Property>
				<Property Name="DestinationID[0]" Type="Str">{1FF69253-E193-4B6D-B6C8-DD3B829FD7CD}</Property>
				<Property Name="DestinationItemCount" Type="Int">1</Property>
				<Property Name="DestinationName[0]" Type="Str">Destination Directory</Property>
				<Property Name="IncludedItemCount" Type="Int">1</Property>
				<Property Name="IncludedItems[0]" Type="Ref">/My Computer</Property>
				<Property Name="IncludeProject" Type="Bool">true</Property>
				<Property Name="Path[0]" Type="Path">../../builds/INA231/INA231-SFT-sourcecode_rev1/INA231.zip</Property>
				<Property Name="ZipBase" Type="Str">NI_zipbasedefault</Property>
			</Item>
		</Item>
	</Item>
</Project>
