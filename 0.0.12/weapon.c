// KEY:0x2A5A8EAD



ammoclass_max_carry CLASS_MANA		500
ammoclass_max_carry CLASS_RGRENADE	300	
ammoclass_max_carry CLASS_GRENADEHE 500
ammoclass_max_carry CLASS_GRENADEFB 5	
ammoclass_max_carry CLASS_GRENADESM 3	

ammoclass_max_carry CLASS_45cal		2800
ammoclass_max_carry CLASS_9mm		3000
ammoclass_max_carry CLASS_9MMSMG	3000
ammoclass_max_carry CLASS_SGSHELL	1400
ammoclass_max_carry CLASS_556MM		8300
ammoclass_max_carry CLASS_556MMSAW	6000
ammoclass_max_carry CLASS_762MMAUTO	6000
ammoclass_max_carry CLASS_762HPBT	2000
ammoclass_max_carry CLASS_50CAL		1000
ammoclass_max_carry CLASS_300MAG	1800
ammoclass_max_carry CLASS_40MMNADE	6000
ammoclass_max_carry CLASS_SATCHEL	2000
ammoclass_max_carry CLASS_CLAYMORE	2000
ammoclass_max_carry CLASS_AT4		1000





weapon "WPN_KNIFE"
	category 1
	rank     0
	statid 100

	charfilter cqb
	charfilter medic
	charfilter sniper
	charfilter gunner

	round_type  "AMMO_KNIFE01"
	clipsize    -1
	startrounds -1
	error_hip	0 
	error_up  	0 
	targetpitchmax  85				
	targetpitchmin  85				
	targetyawrange  120				
	launchuserpoint bullet

	attack_anim	 1		
	special_hold 1		
	run_anim	 1		

	flags Underwater
	flags auto

	crosshair coma20mm.tga
	hudicon H_knife.tga

	animadm knife1ST
//	animadm m9k_1st

	gfx1 knife1ST
//	gfx1 M9k_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
  	gfx3 M9K_3rd 
	POS			20	0	-200	0	0	0
	TPOS		20	0	-199	0	0	0

	action "idle"
		delayend		  auto
		anim		  anim_wpn_idle
		function      wpn_std_idle
	end

	action "emptyidle"
		function			wpn_std_emptyidle
	end

	action "fire"
		delaystart		5
		delayend		auto
		soundsetend		GS_KNIFE
		anim			anim_wpn_fire
		function		wpn_std_fire
	end

	action "recoil"
		delaystart	auto
		//anim		  anim_wpn_fire
		function      wpn_std_recoil
	end

	action "reload"
		delayend		1
		anim		  anim_wpn_reload
		function      wpn_std_reload
	end

	action "empty"
		delaystart			0
		delayend			auto
		anim		  anim_wpn_empty
		function      wpn_std_empty
	end

	action "switchto"
		soundset	GF_KNIFE_ST
		delaystart		1
		delayend		1
		anim		  anim_wpn_switchto
		function      wpn_std_switchto
	end

	action "switchfrom"
		soundset		GF_KNIFE_SF
		delaystart		1
		delayend		1
		//anim		  anim_wpn_switchfrom
		function      wpn_std_switchfrom
	end

	action "switchrank"
		delaystart		1
		delayend		1
		//anim		  anim_wpn_switchrank
		function      wpn_std_switchrank
	end
end


weapon "WPN_colt45"
	category 2
	rank     0
	statid 200

	charfilter cqb
	charfilter medic
	charfilter sniper
	charfilter gunner

	loadout_selectable	1	
	loadout_subclasses	0	

	loadout_menu_icon	tbd.tga
	loadout_menu_textid	WEAP_SHORT_COLT45
	loadout_menu_ttdesc WEAP_DESC_COLT45
	weapon_class	secondary

	round_type		"AMMO_COLT_45"
	clipsize		7
	startrounds		70
	error_hip	.4
	error_up  	.084
	targetpitchmax  85				
	targetpitchmin  85				
	targetyawrange  120				
	ammoclass		CLASS_45cal		1
	launchuserpoint bullet

	special_hold 1		

	ANIMADM	Pistol1_1st
//	animadm colt_1st

	GFX1	1911_1st
//	gfx1 colt_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 colt_3rd
	POS		-5.064	15.055	-198.182	000.000	000.000	000.000
	//TPOS	-50.000	31.200	-188.250	000.000	359.500	000.000


	crosshair coma20mm.tga
	hudicon H_colt.tga
	hudclipgfx 	 0  0		H_clip.tga			
	hudrndgfx	 8  0 18 0 1	H_round.tga	    

	ACTION	"IDLE"
	DELAYEND	auto
	ANIM	ANIM_WPN_IDLE
	FUNCTION	WPN_STD_IDLE
	END

	ACTION	"EMPTYIDLE"
	DELAYEND	auto
	ANIM	ANIM_WPN_EMPTY
	FUNCTION	wpn_std_empty
	END


	action "fire"
		delayend				4
		soundsetend			GS_45
		anim				anim_wpn_fire
		function			wpn_std_fire
		particle			Effect_Colt45MF
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			0
		anim				anim_wpn_recoil
		function			wpn_std_recoil
		particle			Effect_Colt45Cas
		particleuserpoint	bcasing
	end

	action "reload"
		delaystart			50
		delayend				auto
		soundset			GF_BERETTA_RL
		anim				anim_wpn_reload
		function			wpn_std_reload
	end

	action "empty"
		delayend				auto
		soundset			DRY_PISTOL  
		anim				anim_wpn_empty
		function			wpn_std_empty
	end

	action "switchto"
		soundset		GF_45_ST
		delaystart		1
		delayend		1
		anim				anim_wpn_switchto
		function			wpn_std_switchto
	end

	action "switchfrom"
		soundset		GF_45_SF
		delaystart		1
		delayend		1
		anim				anim_wpn_switchfrom
		function			wpn_std_switchfrom
	end

	action "switchrank"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchrank
		function			wpn_std_switchrank
	end
end


weapon "WPN_M9Beretta"
	category 2
	rank     1
	statid	201

	charfilter cqb
	charfilter medic
	charfilter sniper
	charfilter gunner

	loadout_selectable	1	
	loadout_subclasses	0	

	loadout_menu_icon	tbd.tga
	loadout_menu_textid	WEAP_SHORT_M9BERETTA
	loadout_menu_ttdesc WEAP_DESC_M9BERETTA
	weapon_class	secondary

	round_type		"AMMO_BERETTA_9MM"
	clipsize		15
	startrounds		90
	error_hip	.40
	error_up  	.067
	targetpitchmax  85				
	targetpitchmin  85				
	targetyawrange  120				
	ammoclass		CLASS_9mm		1
	launchuserpoint bullet

	special_hold 1		

	ANIMADM	Pistol1_1st
//	animadm M9_1st

	gfx1 M9_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 M9_3RD
	POS		-5.064	15.055	-198.182	000.000	000.000	000.000
	//TPOS	-50.000	31.200	-184.750	000.000	359.250	000.000


	crosshair coma20mm.tga
	hudicon H_bereta.tga
	hudclipgfx 	 0  0		H_clip.tga			
	hudrndgfx	 6  0 8 0 1	H_round.tga	    

	action "idle"
		delayend				auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "emptyidle"
		delayend				auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	


	action "fire"
		delayend				5
		soundsetend			GS_BERETTA
		anim				anim_wpn_fire
		function			wpn_std_fire
		particle			Effect_BrtaMuzFlash
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			0
		anim				anim_wpn_recoil
		function			wpn_std_recoil
		particle			Effect_BrtaBCasing
		particleuserpoint	bcasing
	end

	action "reload"
		delaystart			50
		delayend				auto
		soundset			GF_BERETTA_RL
		anim				anim_wpn_reload
		function			wpn_std_reload
	end

	action "empty"
		delayend				auto
		soundset			DRY_PISTOL	 
		anim				anim_wpn_empty
		function			wpn_std_empty
	end

	action "switchto"
		soundset		GF_45_ST
		delaystart		1
		delayend		1
		anim				anim_wpn_switchto
		function			wpn_std_switchto
	end

	action "switchfrom"
		soundset		GF_45_SF
		delaystart		1
		delayend		1
		anim				anim_wpn_switchfrom
		function			wpn_std_switchfrom
	end

	action "switchrank"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchrank
		function			wpn_std_switchrank
	end
end

weapon "WPN_RemmingtonSG"
	category 2
	rank     2
	statid 202

	charfilter cqb
	//charfilter gunner
	charfilter medic

	loadout_selectable	1	
	loadout_subclasses	0	

	loadout_menu_icon	tbd.tga
	loadout_menu_textid	WEAP_SHORT_SHOTGUN
	loadout_menu_ttdesc WEAP_DESC_SHOTGUN
	weapon_class	secondary

	round_type		"AMMO_SHOTGUN"
	clipsize		7
	startrounds		63
	error_hip	 0   
	error_up  	 0  
	targetpitchmax  85				
	targetpitchmin  85				
	targetyawrange  120				
	ammoclass		CLASS_SGSHELL		1
	launchuserpoint bullet

	special_hold 0		
	flags auto
	animadm R870_1st
//	animadm shtg_1st

	gfx1 R870_1st
//	gfx1 shtg_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 shtg_3RD
	pos		0.064	20.055	-198.182		0.0		0.0		0.0
	//TPOS	-30.049	33.344	-186.432		-0.004	-89.3	0

	crosshair coma20mm.tga
	hudicon H_shtgun.tga
	hudclipgfx 	 0  0		H_clip.tga			
	hudrndgfx	 8  0 18 0 1	H_round.tga	    

	action "idle"
		delayend				auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "emptyidle"
		delayend				auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	


	action "fire"
		delayend				20
		soundsetend			GS_12GAGE_REMM
		anim				anim_wpn_fire
		function			wpn_std_fire
		particle			Effect_RemingtonSGMF
		particleuserpoint	mflash01
	end

	action "recoil"
		delaystart			20
		delayend			auto
		soundset			GF_12GAGE_REC
		anim				anim_wpn_recoil
		function			wpn_std_recoil
		//particle			Effect_RemingtonShel
		particleuserpoint	bcasing
	end

	action "reload"
		delaystart			100
		delayend				auto
		soundset			GF_12GAGE_RL
		anim				anim_wpn_reload
		function			wpn_std_reload
	end

	action "empty"
		delayend				auto
		soundset			DRY_12GAGE
		anim				anim_wpn_empty
		function			wpn_std_empty
	end

	action "switchto"
		soundset		GF_12GAGE_ST
		delaystart		1
		delayend		1
		anim				anim_wpn_switchto
		function			wpn_std_switchto
	end

	action "switchfrom"
		soundset		GF_12GAGE_SF
		delaystart		1
		delayend		1
		anim				anim_wpn_switchfrom
		function			wpn_std_switchfrom
	end

	action "switchrank"
		delaystart		61
		delayend		1
		anim				anim_wpn_switchrank
		function			wpn_std_switchrank
	end
end


weapon "WPN_Saiga"
	category 3
	rank     1
	statid 902

	charfilter cqb
	//charfilter gunner
	charfilter medic

	loadout_selectable	1	
	loadout_subclasses	0	

	loadout_menu_icon	tbd.tga
	loadout_menu_textid	WEAP_SHORT_SAIGA
	loadout_menu_ttdesc WEAP_DESC_Saiga
	weapon_class	primary

	round_type		"12GA"
	clipsize		10
	startrounds		240
	classrounds		medic 200
	classrounds		cqb 200
	error_hip	 0   
	error_up  	 0  
	targetpitchmax  85				
	targetpitchmin  85				
	targetyawrange  120				
	ammoclass		CLASS_762MMAUTO		1
	launchuserpoint bullet
	FLAGS	SIGHTED

	SIGHTS	DOT_RED2.tga		508	380	516	388	blend scale
	SIGHTS	DOT_RED1.tga		508	380	516	388	add	scale
	SIGHTS	PKASRING.TGA		493	365	530	403	blend
	SIGHTS	PKAS_SGT.TGA		300	140	715	768	blend

	special_hold 0		
	animadm AKM_1st

	gfx1 saiga
//	gfx1 shtg_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 saiga3
	pos		10.0		0.0		-201.0			0.0		0.0		1.0
	TPOS	-30.071	21.536	-199.564		0.0		0.0		0.0

	crosshair coma20mm.tga
	hudicon H_saiga.tga
	hudclipgfx 	 0  0		H_clip.tga			
	hudrndgfx	 8  0 18 0 1	H_round.tga	    

	action "idle"
		delayend				auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "emptyidle"
		delayend				auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	


	action "fire"
		delayend				8
		soundsetend			GS_12GAGE_REMM
		anim				anim_wpn_fire
		function			wpn_std_fire
		particle			Effect_RemingtonSGMF
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			0
		anim				anim_wpn_recoil
		function			wpn_std_recoil
		particle			Effect_RemingtonShel
		particleuserpoint	bcasing
	end

	action "reload"
		delaystart			100
		delayend				auto
		soundset			GF_RL_AK47
		anim				anim_wpn_reload
		function			wpn_std_reload
	end

	action "empty"
		delayend				auto
		soundset			DRY_12GAGE
		anim				anim_wpn_empty
		function			wpn_std_empty
	end

	action "switchto"
		soundset		GF_12GAGE_ST
		delaystart		1
		delayend		1
		anim				anim_wpn_switchto
		function			wpn_std_switchto
	end

	action "switchfrom"
		soundset		GF_12GAGE_SF
		delaystart		1
		delayend		1
		anim				anim_wpn_switchfrom
		function			wpn_std_switchfrom
	end

	action "switchrank"
		delaystart		61
		delayend		1
		anim				anim_wpn_switchrank
		function			wpn_std_switchrank
	end
end


weapon "WPN_CAR15AUTO"
	category 3
	rank     0
	statid 300

	charfilter cqb
	charfilter medic
	//charfilter gunner

	loadout_selectable	1	
	loadout_subclasses	1	

	loadout_menu_icon	car15.tga
	loadout_menu_textid	WEAP_SHORT_CAR15
	loadout_menu_ttdesc WEAP_DESC_CAR15
	weapon_class	primary

	round_type		"AMMO_C723_556MM"
	clipsize		30
	startrounds		540
	classrounds		medic 330
	classrounds		cqb 330
	error_hip	.1	
	error_up  	.067  
	targetpitchmax  22				
	targetpitchmin  50				
	targetyawrange  120				
	ammoclass		CLASS_556MM	1
	clipslot		1
	launchuserpoint bullet

	flags auto
	flags Sighted

	SIGHTS	AIMPTSGT.TGA		134	17	890	773	blend
	SIGHTS	DOT_RED2.tga		508	380	516	388	blend scale
	SIGHTS	DOT_RED1.tga		508	380	516	388	add	scale

	crosshair coma20mm.tga
	hudicon H_cr15a.tga
	hudclipgfx 	 0  0		H_clip.tga			
	hudrndgfx	 4  0 4 0 1	H_round.tga	    

	ANIMADM		C723_1ST
//	animadm CR15_1st

	GFX1	C723_1st
//	gfx1 CR15_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 CR15_3RD
	pos		0.000	0.000	-205.182		0.0		0.0		0.0
	TPOS	-39.361	21.830	-202.524		0.0		0.0		0.0

	action "idle"
		delayend				auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "emptyidle"
		delayend				auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	


	action "fire"
		delayend				3
		soundsetend			GS_C723
		anim				anim_wpn_fire
		function			wpn_std_fire
		particle			Effect_MP5MF
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			0
		anim				anim_wpn_recoil
		function			wpn_std_recoil
		particle			Effect_CAR15Cas
		particleuserpoint	bcasing
	end

	action "reload"
		delaystart			100
		delayend			auto
		soundset			GF_RL_AR15_2
		anim				anim_wpn_reload
		function			wpn_std_reload
	end

	action "empty"
		delayend				auto
		soundset			DRY_OICW	
		anim				anim_wpn_empty
		function			wpn_std_empty
	end

	action "switchto"
		soundset		GF_CAR15_ST
		delaystart		1
		delayend		1
		anim				anim_wpn_switchto
		function			wpn_std_switchto
	end

	action "switchfrom"
		soundset		GF_CAR15_SF
		delaystart		1
		delayend		1
		anim				anim_wpn_switchfrom
		function			wpn_std_switchfrom
	end

	action "switchrank"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchrank
		function			wpn_std_switchrank
	end
end

weapon "WPN_CAR15"
	category 3
	rank     1
	statid 301

	charfilter cqb
	charfilter medic
	//charfilter gunner

	round_type		"AMMO_C723_556MM"
	clipsize		30
	startrounds		0
	error_hip	.1 
	error_up  	.067 
	targetpitchmax  85				
	targetpitchmin  85				
	targetyawrange  120				
	ammoclass		CLASS_556MM	1
	clipslot		1
	launchuserpoint bullet

	flags Sighted
	flags Primary

	SIGHTS	AIMPTSGT.TGA		134	17	890	773	blend
	SIGHTS	DOT_RED2.tga		508	380	516	388	blend scale
	SIGHTS	DOT_RED1.tga		508	380	516	388	add	scale

	crosshair coma20mm.tga
	hudicon H_cr15s.tga
	hudclipgfx 	 0  0		H_clip.tga			
	hudrndgfx	 4  0 4 0 1	H_round.tga	    

	ANIMADM		C723_1ST
//	animadm CR15_1st

	GFX1	C723_1st
//	gfx1 CR15_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 CR15_3RD
	pos		0.000	0.000	-205.182		0.0		0.0		0.0
	TPOS	-39.361	21.830	-202.524		0.0		0.0		0.0

	action "idle"
		delayend		  auto
		anim		  anim_wpn_idle
		function      wpn_std_idle
	end	

	action "emptyidle"
		delayend		  auto
		anim		  anim_wpn_idle
		function      wpn_std_idle
	end	

	action "fire"
		delayend				2
		soundsetend			GS_C723
		anim				anim_wpn_fire
		function			wpn_std_fire
		particle			Effect_MP5MF
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			0
		anim				anim_wpn_recoil
		function			wpn_std_recoil
		particle			Effect_CAR15Cas
		particleuserpoint	bcasing
	end

	action "reload"
		delaystart			100
		delayend			auto
		soundset			GF_RL_AR15_2
		anim				anim_wpn_reload
		function			wpn_std_reload
	end

	action "empty"
		delayend				auto
		soundset			DRY_OICW	
		anim				anim_wpn_empty
		function			wpn_std_empty
	end

	action "switchto"
		soundset			GF_CAR15_ST
		delaystart		1
		delayend		1
		anim				anim_wpn_switchto
		function			wpn_std_switchto
	end

	action "switchfrom"
		soundset				GF_CAR15_SF
		delaystart		1
		delayend		1
		anim				anim_wpn_switchfrom
		function			wpn_std_switchfrom
	end

	action "switchrank"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchrank
		function			wpn_std_switchrank
	end
end


weapon "WPN_CAR15M203AUTO"
	category 3
	rank     2
	statid 302

	charfilter cqb
	charfilter gunner

	loadout_selectable	1	
	loadout_subclasses	2	

	loadout_menu_icon	car15.tga
	loadout_menu_textid	WEAP_SHORT_CAR15M203
	loadout_menu_ttdesc WEAP_DESC_CAR15M203
	weapon_class	primary

	round_type		"AMMO_CAR15_556MM"
	clipsize		30
	startrounds		0
	error_hip	.1 
	error_up  	.05 
	targetpitchmax  22				
	targetpitchmin  50				
	targetyawrange  120				
	ammoclass		CLASS_556MM	1
	clipslot		2
	launchuserpoint bullet

	flags auto
	flags Sighted

	SIGHTS	AIMPTSGT.TGA		134	17	890	773	blend
	SIGHTS	DOT_RED2.tga		508	380	516	388	blend scale
	SIGHTS	DOT_RED1.tga		508	380	516	388	add	scale

	crosshair coma20mm.tga
	hudicon H_cr203a.tga
	hudclipgfx 	 0  0		H_clip.tga			
	hudrndgfx	 4  0 4 0 1	H_round.tga	    

	animadm m4GL_1st
//	animadm m203_1st

	gfx1 M4GL_1st
//	gfx1 CR203_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 CR203_3RD
	pos		0.000	0.000	-205.182		0.0		0.4		0.0
	TPOS	-50.902	23.906	-188.846		0.0		0.0		0.0

	action "idle"
		delayend				auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "emptyidle"
		delayend				auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	


	action "fire"
		delayend				3
		soundsetend			GS_CAR151
		anim				anim_wpn_fire
		function			wpn_std_fire
		particle			Effect_CAR15MF
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			0
		anim				anim_wpn_recoil
		function			wpn_std_recoil
		particle			Effect_CAR15Cas
		particleuserpoint	bcasing
	end

	action "reload"
		delaystart			100
		delayend			auto
		soundset			GF_RL_AR15_2
		anim				anim_wpn_reload
		function			wpn_std_reload
	end

	action "empty"
		delayend				auto
		soundset			DRY_OICW	
		anim				anim_wpn_empty
		function			wpn_std_empty
	end

	action "switchto"
		soundset		GF_CAR15_ST
		delaystart		1
		delayend		1
		anim				anim_wpn_switchto
		function			wpn_std_switchto
	end

	action "switchfrom"
		soundset		GF_CAR15_SF
		delaystart		1
		delayend		1
		anim				anim_wpn_switchfrom
		function			wpn_std_switchfrom
	end

	action "switchrank"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchrank
		function			wpn_std_switchrank
	end
end

weapon "WPN_CAR15M203"
	category 3
	rank     3
	statid 303


	charfilter cqb
	charfilter gunner

	round_type		"AMMO_CAR15_556MM"
	clipsize		30
	startrounds		540
	classrounds		gunner 240
	classrounds		cqb 300
	error_hip	.1 
	error_up  	.05 
	targetpitchmax  85				
	targetpitchmin  85				
	targetyawrange  120				
	ammoclass		CLASS_556MM	1
	clipslot		2
	launchuserpoint bullet

	flags Sighted
	flags Primary

	SIGHTS	AIMPTSGT.TGA		134	17	890	773	blend
	SIGHTS	DOT_RED2.tga		508	380	516	388	blend scale
	SIGHTS	DOT_RED1.tga		508	380	516	388	add	scale

	crosshair coma20mm.tga
	hudicon H_cr203s.tga
	hudclipgfx 	 0  0		H_clip.tga			
	hudrndgfx	 4  0 4 0 1	H_round.tga	    

	animadm m4GL_1st
//	animadm m203_1st

	gfx1 M4GL_1st
//	gfx1 CR203_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 CR203_3RD
	pos		0.000	0.000	-205.182		0.0		0.4		0.0
	TPOS	-50.902	23.906	-188.846		0.0		0.0		0.0

	action "idle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "emptyidle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "fire"
		delayend				3
		soundsetend			GS_CAR151
		anim				anim_wpn_fire
		function			wpn_std_fire
		particle			Effect_CAR15MF
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			0
		anim				anim_wpn_recoil
		function			wpn_std_recoil
		particle			Effect_CAR15Cas
		particleuserpoint	bcasing
	end

	action "reload"
		delaystart			100
		delayend			auto
		soundset			GF_RL_AR15_2
		anim				anim_wpn_reload
		function			wpn_std_reload
	end

	action "empty"
		delayend				auto
		soundset			DRY_OICW	
		anim				anim_wpn_empty
		function			wpn_std_empty
	end

	action "switchto"
		soundset			GF_CAR15_ST
		delaystart		1
		delayend		1
		anim				anim_wpn_switchto
		function			wpn_std_switchto
	end

	action "switchfrom"
		soundset				GF_CAR15_SF
		delaystart		1
		delayend		1
		anim				anim_wpn_switchfrom
		function			wpn_std_switchfrom
	end

	action "switchrank"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchrank
		function			wpn_std_switchrank
	end
end


weapon "WPN_CAR15M203HE"
	category 3
	rank     4
	statid 304


	charfilter cqb
	charfilter gunner

	round_type		"AMMO_M203_40MM_NADE"
	clipsize		1
	startrounds		18
	classrounds		gunner 12
	classrounds		cqb 6
	error_hip	.2  
	error_up  	.2  
	targetpitchmax  22				
	targetpitchmin  50				
	targetyawrange  120				
	ammoclass		CLASS_40MMNADE	1
	launchuserpoint bullet

	flags Sighted
	flags	AutoLob

	scope_max_zero 10 50 0

	sights  m16203b.tga   112  -68 892 703 blendat slide 33
	SIGHTS	AIMPTSGT.TGA		134	17	890	773	blend
	SIGHTS	DOT_RED2.tga		508	380	516	388	blend scale
	SIGHTS	DOT_RED1.tga		508	380	516	388	add	scale


	crosshair coma20mm.tga
	hudicon H_cr203g.tga
	hudclipgfx 	 0  0		H_clip.tga			
	hudrndgfx	 12  0 20 0 1	H_round.tga	    

	animadm m4GL_2nd
//	animadm m203_2nd

	gfx1 M4GL_1st
//	gfx1 CR203_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 CR203_3RD
	pos		0.000	0.000	-205.182		0.0		0.4		0.0
	TPOS	-50.902	23.906	-188.846		0.0		0.0		0.0

	action "idle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "emptyidle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	


	action "fire"
		delayend				auto
		soundsetend			GS_M203_GLAUNCH
		anim				anim_wpn_fire
		function			wpn_std_fire
		particle			Effect_M4GrenMF
		particleuserpoint	mflash02
	end

	action "recoil"
		delayend			auto
		anim				anim_wpn_recoil
		function			wpn_std_recoil
		
		
	end

	action "reload"
		delaystart			100
		delayend			auto
		soundset			GF_M203G_RL
		anim				anim_wpn_reload
		function			wpn_std_reload
	end

	action "empty"
		delayend			auto
		soundset			DRY_OICW 
		function			wpn_std_empty
	end

	action "switchto"
		soundset		GF_CAR15_ST
		delaystart		1
		delayend		1
		anim				anim_wpn_switchto
		function			wpn_std_switchto
	end

	action "switchfrom"
		soundset		GF_CAR15_SF
		delaystart		1
		delayend		1
		anim				anim_wpn_switchfrom
		function			wpn_std_switchfrom
	end

	action "switchrank"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchrank
		function			wpn_std_switchrank
	end
end


weapon "WPN_M16BURST"
	category 3
	rank     5
	statid 305


	charfilter cqb
	charfilter medic
	charfilter gunner

	loadout_selectable	1	
	loadout_subclasses	1	

	loadout_menu_icon	car15.tga
	loadout_menu_textid	WEAP_SHORT_M16
	loadout_menu_ttdesc WEAP_DESC_M16
	weapon_class	primary

	round_type		"AMMO_M16_556MM"
	clipsize		30
	startrounds		540
	classrounds		medic 210
	classrounds		gunner 600
	classrounds		cqb 330
	error_hip	.1
	error_up  	.042 
	targetpitchmax  22				
	targetpitchmin  50				
	targetyawrange  120				
	ammoclass		CLASS_556MM	1
	clipslot		3
	launchuserpoint bullet

	flags burst
	flags Sighted

	SIGHTS		M4ET_SGT.TGA		196	255	780	798	blend
	SIGHTS		et_rtcle.tga		486	358	538	410	add	scale

	crosshair coma20mm.tga
	hudicon H_16a.tga
	hudclipgfx 	 0  0		H_clip.tga			
	hudrndgfx	 4  0 4 0 1	H_round.tga	    

	ANIMADM	M4_1ST
//	animadm m16_1st

	GFX1	m16ET1st
//	gfx1 m16_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 m16_3RD
	pos		0.000	0.000	-205.182		0.0		0.4		0.0
	TPOS	-27.057	23.95	-189.75		0.0		0.2		0.0

	action "idle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "emptyidle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	


	action "fire"
		delayend				3
		soundsetend			GS_M16
		anim				anim_wpn_fire
		function			wpn_std_fire
		particle			Effect_M16MF
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			0
		anim				anim_wpn_recoil
		function			wpn_std_recoil
		particle			Effect_M16Cas
		particleuserpoint	bcasing
	end

	action "reload"
		delaystart			100
		delayend			auto
		soundset			GF_RL_AR15_2
		anim				anim_wpn_reload
		function			wpn_std_reload
	end

	action "empty"
		delayend				auto
		soundset			DRY_M16	
		anim				anim_wpn_empty
		function			wpn_std_empty
	end

	action "switchto"
		soundset		GF_CAR15_ST
		delaystart		1
		delayend		1
		anim				anim_wpn_switchto
		function			wpn_std_switchto
	end

	action "switchfrom"
		soundset		GF_CAR15_SF
		delaystart		1
		delayend		1
		anim				anim_wpn_switchfrom
		function			wpn_std_switchfrom
	end

	action "switchrank"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchrank
		function			wpn_std_switchrank
	end
end

weapon "WPN_M16"
	category 3
	rank     6
	statid 306

	charfilter cqb
	charfilter medic
	charfilter gunner

	round_type		"AMMO_M16_556MM"
	clipsize		30
	startrounds		0
	error_hip	.1
	error_up  	.042 
	targetpitchmax  22				
	targetpitchmin  50				
	targetyawrange  120				
	ammoclass		CLASS_556MM	1
	clipslot		3
	launchuserpoint bullet

	flags Sighted

	SIGHTS		M4ET_SGT.TGA		196	255	780	798	blend
	SIGHTS		et_rtcle.tga		486	358	538	410	add	scale


	crosshair coma20mm.tga
	hudicon H_16s.tga
	hudclipgfx 	 0  0		H_clip.tga			
	hudrndgfx	 4  0 4 0 1	H_round.tga	    

	ANIMADM	M4_1ST
//	animadm m16_1st

	GFX1	m16ET1st
//	gfx1 m16_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 m16_3RD
	pos		0.000	0.000	-205.182		0.0		0.4		0.0
	TPOS	-27.057	23.95	-189.75		0.0		0.2		0.0

	action "idle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "emptyidle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	


	action "fire"
		delayend				2
		soundsetend			GS_M16
		anim				anim_wpn_fire
		function			wpn_std_fire
		particle			Effect_M16MF
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			1
		anim				anim_wpn_recoil
		function			wpn_std_recoil
		particle			Effect_M16Cas
		particleuserpoint	bcasing
	end

	action "reload"
		delaystart			100
		delayend			auto
		soundset			GF_RL_AR15_2
		anim				anim_wpn_reload
		function			wpn_std_reload
	end

	action "empty"
		delayend				auto
		soundset			DRY_M16	
		anim				anim_wpn_empty
		function			wpn_std_empty
	end

	action "switchto"
		soundset		GF_CAR15_ST
		delaystart		1
		delayend		1
		anim				anim_wpn_switchto
		function			wpn_std_switchto
	end

	action "switchfrom"
		soundset		GF_CAR15_SF
		delaystart		1
		delayend		1
		anim				anim_wpn_switchfrom
		function			wpn_std_switchfrom
	end

	action "switchrank"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchrank
		function			wpn_std_switchrank
	end
end


weapon "WPN_M16M203BURST"
	category 3
	rank     7
	statid 307

	charfilter cqb
	charfilter gunner

	loadout_selectable	1	
	loadout_subclasses	2	

	loadout_menu_icon	car15.tga
	loadout_menu_textid	WEAP_SHORT_M16M203
	loadout_menu_ttdesc WEAP_DESC_M16M203
	weapon_class	primary

	round_type		"AMMO_M16_556MM"
	clipsize		30
	startrounds		540
	classrounds		gunner 240
	classrounds		cqb 300
	error_hip	.1 
	error_up  	.042 
	targetpitchmax  22				
	targetpitchmin  50				
	targetyawrange  120				
	ammoclass		CLASS_556MM	1
	clipslot		4
	launchuserpoint bullet

	flags burst
	flags Sighted

	SIGHTS	M16irn_F.TGA		468	359	556	536		blend
	SIGHTS	M16irn_R.TGA		25	275	977	771		blend

	crosshair coma20mm.tga
	hudicon H_16203a.tga
	hudclipgfx 	 0  0		H_clip.tga			
	hudrndgfx	 4  0 4 0 1	H_round.tga	    

	animadm m203_1st

	gfx1 m203_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 m203_3RD
	pos		0.000	0.000	-205.182		0.0		0.4		0.0
	TPOS	-27.057	23.906	-189.75		0.0		0.2		0.0

	action "idle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "emptyidle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	


	action "fire"
		delayend				1
		soundsetend			GS_M16
		anim				anim_wpn_fire
		function			wpn_std_fire
		particle			Effect_M16MF
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			2
		anim				anim_wpn_recoil
		function			wpn_std_recoil
		particle			Effect_M16Cas
		particleuserpoint	bcasing
	end

	action "reload"
		delaystart			100
		delayend			auto
		soundset			GF_RL_AR15_2
		anim				anim_wpn_reload
		function			wpn_std_reload
	end

	action "empty"
		delayend				auto
		soundset			DRY_M16	
		anim				anim_wpn_empty
		function			wpn_std_empty
	end

	action "switchto"
		soundset		GF_CAR15_ST
		delaystart		1
		delayend		1
		anim				anim_wpn_switchto
		function			wpn_std_switchto
	end

	action "switchfrom"
		soundset		GF_CAR15_SF
		delaystart		1
		delayend		1
		anim				anim_wpn_switchfrom
		function			wpn_std_switchfrom
	end

	action "switchrank"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchrank
		function			wpn_std_switchrank
	end
end

weapon "WPN_M16M203"
	category 3
	rank     8
	statid 308


	charfilter cqb
	charfilter gunner

	round_type		"AMMO_M16_556MM"
	clipsize		30
	startrounds		0
	error_hip	.1 
	error_up  	.042 
	targetpitchmax  22				
	targetpitchmin  50				
	targetyawrange  120				
	ammoclass		CLASS_556MM	1
	clipslot		4
	launchuserpoint bullet

	flags Sighted

	SIGHTS	M16irn_F.TGA		468	359	556	536		blend
	SIGHTS	M16irn_R.TGA		25	275	977	771		blend

	crosshair coma20mm.tga
	hudicon H_16203s.tga
	hudclipgfx 	 0  0		H_clip.tga			
	hudrndgfx	 4  0 4 0 1	H_round.tga	    

	animadm m203_1st

	gfx1 m203_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 m203_3RD
	pos		0.000	0.000	-205.182		0.0		0.4		0.0
	TPOS	-27.057	23.906	-189.75		0.0		0.2		0.0

	action "idle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "emptyidle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	


	action "fire"
		delayend				2
		soundsetend			GS_M16
		anim				anim_wpn_fire
		function			wpn_std_fire
		particle			Effect_M16MF
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			1
		anim				anim_wpn_recoil
		function			wpn_std_recoil
		particle			Effect_M16Cas
		particleuserpoint	bcasing
	end

	action "reload"
		delaystart			100
		delayend			auto
		soundset			GF_RL_AR15_2
		anim				anim_wpn_reload
		function			wpn_std_reload
	end

	action "empty"
		delayend				auto
		soundset			DRY_M16	
		anim				anim_wpn_empty
		function			wpn_std_empty
	end

	action "switchto"
		soundset		GF_CAR15_ST
		delaystart		1
		delayend		1
		anim				anim_wpn_switchto
		function			wpn_std_switchto
	end

	action "switchfrom"
		soundset		GF_CAR15_SF
		delaystart		1
		delayend		1
		anim				anim_wpn_switchfrom
		function			wpn_std_switchfrom
	end

	action "switchrank"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchrank
		function			wpn_std_switchrank
	end
end



weapon "WPN_M16M203HE"
	category 3
	rank     9
	statid 309

	charfilter cqb
	charfilter gunner

	round_type		"AMMO_M203_40MM_NADE"
	clipsize		1
	startrounds		18
	classrounds		gunner 12
	classrounds		cqb 6
	error_hip	.2
	error_up  	.2  
	targetpitchmax  22				
	targetpitchmin  50				
	targetyawrange  120				
	ammoclass		CLASS_40MMNADE	1
	launchuserpoint bullet

	flags Sighted
	flags	AutoLob

	scope_max_zero 10 50 0
	sights  m16203a.tga   112  0 883 768 blendat
    sights  M16irnB.tga   447  356 576 485 blend
	sights  m16203b.tga   112  -68 892 703 blendat slide 33

	crosshair coma20mm.tga
	hudicon H_16203g.tga
	hudclipgfx 	 0  0		H_clip.tga			
	hudrndgfx	 12  0 20 0 1	H_round.tga	    

	animadm m203_2nd

	gfx1 m203_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 m203_3RD
	pos		0.000	0.000	-205.182		0.0		0.4		0.0
	TPOS	-50.902	23.906	-188.846		0.0		0.0		0.0

	action "idle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "emptyidle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	


	action "fire"
		delayend				auto
		soundsetend			GS_M203_GLAUNCH
		anim				anim_wpn_fire
		function			wpn_std_fire
		particle			Effect_M4GrenMF
		particleuserpoint	mflash02
	end

	action "recoil"
		delayend			auto
		anim				anim_wpn_recoil
		function			wpn_std_recoil
		
		
	end

	action "reload"
		delaystart			100
		delayend			auto
		soundset			GF_M203G_RL
		anim				anim_wpn_reload
		function			wpn_std_reload
	end

	action "empty"
		delayend				auto
		soundset			DRY_OICW 
		function			wpn_std_empty
	end

	action "switchto"
		soundset		GF_CAR15_ST
		delaystart		1
		delayend		1
		anim				anim_wpn_switchto
		function			wpn_std_switchto
	end

	action "switchfrom"
		soundset		GF_CAR15_SF
		delaystart		1
		delayend		1
		anim				anim_wpn_switchfrom
		function			wpn_std_switchfrom
	end

	action "switchrank"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchrank
		function			wpn_std_switchrank
	end
end


weapon "WPN_M21"
	category 3
	rank     10
	statid 310


	charfilter sniper

	flags Sniper

	loadout_selectable	1	
	loadout_subclasses	0	

	loadout_menu_icon	tbd.tga
	loadout_menu_textid	WEAP_SHORT_M21
	loadout_menu_ttdesc WEAP_DESC_M21
	weapon_class	primary

	round_type		"AMMO_M21_762HPBT"
	clipsize		20
	startrounds		200
	error_hip	.6 
	error_up  	.013 
	targetpitchmax  85				
	targetpitchmin  85				
	targetyawrange  120				
	ammoclass		CLASS_762HPBT	1
	launchuserpoint bullet

	flags Scoped
	scope_max_zero 10 100 200
	scope_max_mag	12

	crosshair coma20mm.tga
	hudicon H_m21.tga
	hudclipgfx 	 0  0		H_clip.tga			
	hudrndgfx	 7  0 6 0 1	H_round.tga	    

	animadm M21_1st

	gfx1 M21A_1st
//	gfx1 M21_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 M21_3RD
	pos		1.162	0.000	-198.182	0	0	0
	tpos	-26.434	25.239	-188.664	0	0	0

	action "idle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "emptyidle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "fire"
		delayend				8
		soundsetend			GS_M21
		anim				anim_wpn_fire
		function			wpn_std_fire
		particle			Effect_M21MF
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			0
		//anim				anim_wpn_recoil
		function			wpn_std_recoil
		particle			Effect_M21Cas
		particleuserpoint	bcasing
	end

	action "reload"
		delaystart			90
		delayend			auto
		soundset			GF_M21_RL
		anim				anim_wpn_reload
		function			wpn_std_reload
	end

	action "empty"
		delayend				auto
		soundset			DRY_SNIPE	
		anim				anim_wpn_empty
		function			wpn_std_empty
	end

	action "switchto"
		soundset			GF_M21_ST
		delaystart			1
		delayend			1
		anim				anim_wpn_switchto
		function			wpn_std_switchto
	end

	action "switchfrom"
		soundset			GF_M21_SF
		delaystart		1
		delayend		1
		anim				anim_wpn_switchfrom
		function			wpn_std_switchfrom
	end

	action "switchrank"
		delaystart		27
		delayend		1
		anim				anim_wpn_switchrank
		function			wpn_std_switchrank
	end
end


weapon "WPN_M24"
	category 3
	rank     11
	statid 311


	charfilter sniper

	flags Sniper

	loadout_selectable	1	
	loadout_subclasses	0	

	loadout_menu_icon	tbd.tga
	loadout_menu_textid	WEAP_SHORT_M24
	loadout_menu_ttdesc WEAP_DESC_M24
	weapon_class	primary

	round_type		"AMMO_M24_762HPBT"
	clipsize		6
	startrounds		180
	error_hip	.5 
	error_up  	.008
	targetpitchmax  85				
	targetpitchmin  85				
	targetyawrange  120				
	ammoclass		CLASS_762HPBT	1
	launchuserpoint bullet

	flags Scoped
	scope_max_zero 10 100 200
	scope_max_mag	12

	crosshair coma20mm.tga
	hudicon H_m24.tga
	hudclipgfx 	 0  0		H_clip.tga			
	hudrndgfx	 8  0 18 0 1	H_round.tga	    

	animadm M24_1st

	gfx1 M24_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 M24_3RD
	pos		5.162	0.000	-198.000		2.0		2.0		0.0
	TPOS	-28.046	21.531	-187.857		0.0		0.0		0.0

	action "idle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "emptyidle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "fire"
		delayend				auto
		soundsetend			GS_M24
		anim				anim_wpn_fire
		function			wpn_std_fire
		particle			Effect_M24MF
		particleuserpoint	mflash01
	end

	action "recoil"
		delaystart			60
		delayend			50
		soundset			GF_M24_REC
		anim				anim_wpn_recoil
		function			wpn_std_recoil
		particle			Effect_M24Cas
		particleuserpoint	bcasing
	end

	action "reload"
		delaystart			90
		delayend			auto
		soundset			GF_M24_RL
		anim				anim_wpn_reload
		function			wpn_std_reload
	end

	action "empty"
		delayend				auto
		soundset			DRY_BOLTSNIPE		
		anim				anim_wpn_empty
		function			wpn_std_empty
	end

	action "switchto"
		soundset			GF_M21_ST
		delaystart		1
		delayend		1
		anim				anim_wpn_switchto
		function			wpn_std_switchto
	end

	action "switchfrom"
		soundset			GF_M21_SF
		delaystart		1
		delayend		1
		anim				anim_wpn_switchfrom
		function			wpn_std_switchfrom
	end

	action "switchrank"
		delaystart		50
		delayend		1
		anim				anim_wpn_switchrank
		function			wpn_std_switchrank
	end
end


weapon "WPN_W300" //L115A
	category 3
	rank     12
	statid 312


	charfilter sniper

	flags Sniper

	loadout_selectable	1	
	loadout_subclasses	0	

	loadout_menu_icon	tbd.tga
	loadout_menu_textid	WEAP_SHORT_300MAG
	loadout_menu_ttdesc WEAP_DESC_300MAG
	weapon_class	primary

	round_type		"AMMO_WINCHESTER300_300MAG"
	clipsize		10
	startrounds		180
	error_hip	.5
	error_up  	.008
	targetpitchmax  85				
	targetpitchmin  85				
	targetyawrange  120				
	ammoclass		CLASS_300MAG	1
	launchuserpoint bullet

	flags Scoped
	scope_max_zero 12 100 200
	scope_max_mag	18

	crosshair coma20mm.tga
	hudicon H_win300.tga
	hudclipgfx 	 0  0		H_clip.tga			
	hudrndgfx	 8  0 20 0 1	H_round.tga	    

	animadm L115_1st

	gfx1 L115_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 L115_3RD
	pos		10.169	-5.000	-198.182		2.0		2.0		0.0
	TPOS	-28.046	21.531	-187.857		0.0		0.0		0.0

	action "idle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "emptyidle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "fire"
		delayend				auto
		soundsetend			GS_W300MAG
		anim				anim_wpn_fire
		function			wpn_std_fire
		particle			Effect_M4MuzFlashFp
		particleuserpoint	mflash01
	end

	action "recoil"
		delaystart			60
		delayend			50
		soundset			GF_M24_REC 
		anim				anim_wpn_recoil
		function			wpn_std_recoil
		particle			Effect_M4BCasingFP
		particleuserpoint	bcasing
	end

	action "reload"
		delaystart			90
		delayend			auto
		soundset			GF_M24_RL 
		anim				anim_wpn_reload
		function			wpn_std_reload
	end

	action "empty"
		delayend				auto
		soundset			DRY_BOLTSNIPE	
		anim				anim_wpn_empty
		function			wpn_std_empty
	end

	action "switchto"
		soundset			GF_M21_ST
		delaystart		1
		delayend		1
		anim				anim_wpn_switchto
		function			wpn_std_switchto
	end

	action "switchfrom"
		soundset			GF_M21_SF
		delaystart		1
		delayend		1
		anim				anim_wpn_switchfrom
		function			wpn_std_switchfrom
	end

	action "switchrank"
		delaystart		50
		delayend		1
		anim				anim_wpn_switchrank
		function			wpn_std_switchrank
	end
end


weapon "WPN_Barret"
	category 3
	rank     13
	statid 313


	charfilter sniper

	flags Sniper

	loadout_selectable	1	
	loadout_subclasses	0	

	loadout_menu_icon	tbd.tga
	loadout_menu_textid	WEAP_SHORT_BARRET
	loadout_menu_ttdesc WEAP_DESC_BARRET
	weapon_class	primary

	round_type		"AMMO_BARRET_50CAL"
	clipsize		10
	startrounds		100
	error_hip	3.5 
	error_up  	.047
	targetpitchmax  85				
	targetpitchmin  85				
	targetyawrange  120				
	ammoclass		CLASS_50CAL	1
	launchuserpoint bullet
	

	flags Scoped
	scope_max_zero 10 100 200
	scope_max_mag	16

	crosshair coma20mm.tga
	hudicon H_barret.tga
	hudclipgfx 	 0  0		H_clip.tga			
	hudrndgfx	 7  0 11 0 1	H_round.tga	    

	animadm M82_1st

	gfx1 M82_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 M82_3RD
  	pos		0.000	0.000	-198.182		2.0		2.0		0.0
	TPOS	-28.046	21.531	-187.857		0.0		0.0		0.0

	action "idle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "emptyidle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "fire"
		delayend				auto
		soundsetend			GS_BARRET
		anim				anim_wpn_fire
		function			wpn_std_fire
		particle			Effect_M4MuzFlashFp
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			0
		//anim				anim_wpn_recoil
		function			wpn_std_recoil
		particle			Effect_M4BCasingFP
		particleuserpoint	bcasing
	end

	action "reload"
		delaystart			150
		delayend			auto
		soundset			GF_BARRETT_RL
		anim				anim_wpn_reload
		function			wpn_std_reload
	end

	action "empty"
		delayend				auto
		soundset			DRY_SNIPE	
		anim				anim_wpn_empty
		function			wpn_std_empty
	end

	action "switchto"
		soundset			GF_M21_ST
		delaystart		1
		delayend		1
		anim				anim_wpn_switchto
		function			wpn_std_switchto
	end

	action "switchfrom"
		soundset			GF_M21_SF
		delaystart		1
		delayend		1
		anim				anim_wpn_switchfrom
		function			wpn_std_switchfrom
	end

	action "switchrank"
		delaystart		48
		delayend		1
		anim				anim_wpn_switchrank
		function			wpn_std_switchrank
	end
end


weapon "WPN_M249SAW"	
	category 3
	rank     14
	statid 314


	charfilter gunner

	loadout_selectable	1	
	loadout_subclasses	0	

	loadout_menu_icon	tbd.tga
	loadout_menu_textid	WEAP_SHORT_SAW
	loadout_menu_ttdesc WEAP_DESC_SAW
	weapon_class	primary

	round_type		"AMMO_SAW_556MM"
	clipsize		200
	startrounds		600
	error_hip	1.6 
	error_up  	.033
	targetpitchmax  22				
	targetpitchmin  50				
	targetyawrange  120				
	ammoclass		CLASS_556MMSAW	1
	launchuserpoint bullet

	flags auto
	flags Sighted
	sights  saw_sgt.tga   59 122 979 773 blend

	crosshair coma20mm.tga
	hudicon H_saw.tga
	hudclipgfx 	 0  0		H_clip.tga			
	hudrndgfx	 4  0 4 0 7	H_round.tga	    

	animadm M249_1st

	gfx1 M249_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 M249_3RD
  	pos  20 -5 -209 0 0 0
	tpos	-15 17 -184 2.3 0 0
	
	
	

	action "idle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "emptyidle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	


	action "fire"
		delayend			3 
		soundsetend			GS_SAW
		anim				anim_wpn_fire
		function			wpn_std_fire
		particle			Effect_M249SawMF
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			0
		anim				anim_wpn_recoil
		function			wpn_std_recoil
		particle			Effect_M249SawCas
		particleuserpoint	bcasing
	end

	action "reload"
		delaystart			200
		delayend				auto
		soundset			GF_SAW_RL
		anim				anim_wpn_reload
		function			wpn_std_reload
	end

	action "empty"
		delayend				auto
		soundset			DRY_MG  
		anim				anim_wpn_empty
		function			wpn_std_empty
	end

	action "switchto"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchto
		function			wpn_std_switchto
		soundset	GF_MG_ST
	end

	action "switchfrom"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchfrom
		function			wpn_std_switchfrom
		soundset	GF_MG_SF
	end

	action "switchrank"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchrank
		function			wpn_std_switchrank
	end
end


weapon "WPN_M60"	
	category 3
	rank     15
	statid 315


	charfilter gunner

	loadout_selectable	1	
	loadout_subclasses	0	

	loadout_menu_icon	tbd.tga
	loadout_menu_textid	WEAP_SHORT_M60
	loadout_menu_ttdesc WEAP_DESC_M60
	weapon_class	primary

	round_type		"AMMO_M60_762MM"
	clipsize		100
	startrounds		500
	error_hip	1.5 
	error_up  	.025
	targetpitchmax  22				
	targetpitchmin  50				
	targetyawrange  120				
	ammoclass		CLASS_762MMAUTO	1
	launchuserpoint bullet

	flags auto
	flags Sighted
	SIGHTS	M60Irn_R.tga		0	198	799	788	blend

	crosshair coma20mm.tga
	hudicon H_m60.tga
	hudclipgfx 	 0  0		H_clip.tga			
	hudrndgfx	 4  0 4 0 7	H_round.tga	    

	animadm M249_1st

	gfx1 M60_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 M60_3RD
  	pos  20 -5 -209 0 0 0
	tpos	-19 25 -182 0 0 0

	
	

	action "idle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "emptyidle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	


	action "fire"
		delayend			5
		soundsetend			GS_M60
		anim				anim_wpn_fire
		function			wpn_std_fire
		particle			Effect_M60MF
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			0
		anim				anim_wpn_recoil
		function			wpn_std_recoil
		particle			Effect_M60Cas
		particleuserpoint	bcasing
	end

	action "reload"
		delaystart			200
		delayend				auto
		soundset			GF_M60_RL
		anim				anim_wpn_reload
		function			wpn_std_reload
	end

	action "empty"
		delayend				auto
		soundset			DRY_MG 
		anim				anim_wpn_empty
		function			wpn_std_empty
	end

	action "switchto"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchto
		function			wpn_std_switchto
		soundset	GF_MG_ST
	end

	action "switchfrom"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchfrom
		function			wpn_std_switchfrom
		soundset	GF_MG_SF
	end

	action "switchrank"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchrank
		function			wpn_std_switchrank
	end
end


weapon "WPN_MAG58" //RPK
	category 3
	rank     16
	statid 316

	charfilter gunner

	loadout_selectable	1	
	loadout_subclasses	0	

	loadout_menu_icon	tbd.tga
	loadout_menu_textid	WEAP_SHORT_FNMAG
	loadout_menu_ttdesc WEAP_DESC_FNMAG
	weapon_class	primary

	round_type		"AMMO_RPK_762x39"
	clipsize		75
	startrounds		525
	error_hip	1.0
	error_up  	.042
	targetpitchmax  22				
	targetpitchmin  50				
	targetyawrange  120				
	ammoclass		CLASS_762MMAUTO	1
	launchuserpoint bullet

	flags auto
	FLAGS	SIGHTED

	SIGHTS	AKM_irn.TGA		-45	340	1056	770	blend

	crosshair coma20mm.tga
	hudicon H_mag58.tga
	hudclipgfx 	 0  0		H_clip.tga			
	hudrndgfx	 4  0 4 0 7	H_round.tga	    

	ANIMADM	RPK_1ST

	//renderfov 40
	GFX1	RPK_1st
//	animadm M249_1st

//	gfx1 M58_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 RPK_3RD
	pos		10.0		0.0		-200.0			0.0		0.0		1.0
	TPOS	-28.046	21.531	-187.857		0.0		0.0		0.0

	
	

	action "idle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "emptyidle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	


	action "fire"
		delayend			4
		soundsetend			GS_MAG58
		anim				anim_wpn_fire
		function			wpn_std_fire
		particle			Effect_M4MuzFlashFp
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			0
		anim				anim_wpn_recoil
		function			wpn_std_recoil
		particle			Effect_M4BCasingFP
		particleuserpoint	bcasing
	end

	action "reload"
		delaystart			150
		delayend				auto
		soundset			GF_RL_RPK
		anim				anim_wpn_reload
		function			wpn_std_reload
	end

	action "empty"
		delayend				auto
		soundset			DRY_MG  
		anim				anim_wpn_empty
		function			wpn_std_empty
	end

	action "switchto"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchto
		function			wpn_std_switchto
		soundset	GF_MG_ST
	end

	action "switchfrom"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchfrom
		function			wpn_std_switchfrom
		soundset	GF_MG_SF
	end

	action "switchrank"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchrank
		function			wpn_std_switchrank
	end
end


weapon "WPN_MP5"	
	category 3
	rank     17
	statid 317

	charfilter cqb
	charfilter medic
	
	loadout_selectable	1	
	loadout_subclasses	0	

	loadout_menu_icon	tbd.tga
	loadout_menu_textid	WEAP_SHORT_MP5
	loadout_menu_ttdesc WEAP_DESC_MP5
	weapon_class	primary

	round_type		"AMMO_MP5_9MM"
	clipsize		40
	startrounds		720
	classrounds		medic 440
	classrounds		cqb 440
	error_hip	.1 
	error_up  	.038 
	targetpitchmax  22				
	targetpitchmin  50				
	targetyawrange  120				
	ammoclass		CLASS_9MMSMG	1
	launchuserpoint bullet

	flags auto
	flags Sighted

	sights  MP5irnA.tga   133  4 889 768 blend
	sights  MP5irnB.tga   447  356 576 485 blend

	crosshair coma20mm.tga
	hudicon H_mp5.tga
	hudclipgfx 	 0  0		H_clip.tga			
	hudrndgfx	 4  0 4 0 1	H_round.tga	    

	animadm Mp5_1st

	gfx1 Mp5s_1st
//	gfx1 Mp5_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 Mp5_3RD
	pos		0.0		0.0		-200.0				0.0		0.4		1.0
	TPOS	-27.818	24.759	-179.085		0.0		0.4		0.0

	action "idle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "emptyidle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	


	action "fire"
		delayend			3
		soundsetend			GS_MP5SUP
		anim				anim_wpn_fire
		function			wpn_std_fire
		particle			Effect_MP5MF
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			0
		//anim				anim_wpn_recoil
		function			wpn_std_recoil
		particle			Effect_BrtaBCasing
		particleuserpoint	bcasing
	end

	action "reload"
		delaystart			60
		delayend				auto
		soundset			GF_MP5_RL
		anim				anim_wpn_reload
		function			wpn_std_reload
	end

	action "empty"
		delayend				auto
		soundset			DRY_MP5  
		anim				anim_wpn_empty
		function			wpn_std_empty
	end

	action "switchto"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchto
		function			wpn_std_switchto
		soundset	GF_MP5_ST
	end

	action "switchfrom"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchfrom
		function			wpn_std_switchfrom
		soundset	GF_MP5_SF
	end

	action "switchrank"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchrank
		function			wpn_std_switchrank
	end
end

weapon "WPN_G3AUTO"
	category 3
	rank     18
	statid 318
	flags teamsabre

	charfilter cqb
	charfilter gunner
	charfilter medic

	loadout_selectable	1	
	loadout_subclasses	1	

	loadout_menu_icon	G3.tga
	loadout_menu_textid	WEAP_SHORT_G3
	loadout_menu_ttdesc 	WEAP_DESC_G3
	weapon_class		primary

	round_type		"AMMO_G3_762MM"
	clipsize		20
	startrounds		360
	classrounds		medic 200
	classrounds		gunner 400
	classrounds		cqb 300
	error_hip	.1
	error_up  	.058
	targetpitchmax  22				
	targetpitchmin  50				
	targetyawrange  120				
	ammoclass		CLASS_556MM	1
	clipslot		1
	launchuserpoint bullet

	flags auto
	flags Sighted


	sights  G3_sgt2.tga		462 385 563 457 blend
	sights  G3_sgt.tga		200 295 823 824	blend
	
	

	crosshair coma20mm.tga
	hudicon H_g3a.tga
	hudclipgfx 	 0  0		H_clip.tga			
	hudrndgfx	 7  0 6 0 1	H_round.tga	    

	animadm G3_1st

	gfx1 G3_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 G3_3rd
	pos		0.0		0.0		-200.0				0.0		0.4		1.0
	TPOS	-15.0		24.759	-184.423		0.0		0.4		0.0
	
	action "idle"
		delayend				auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "emptyidle"
		delayend				auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	


	action "fire"
		delayend			6	
		soundsetend			GS_HKG3A
		anim				anim_wpn_fire
		function			wpn_std_fire
		particle			Effect_CAR15MF
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			0
		anim				anim_wpn_recoil
		function			wpn_std_recoil
		particle			Effect_CAR15Cas
		particleuserpoint	bcasing
	end

	action "reload"
		delaystart			100
		delayend			auto
		soundset			GF_HKG3A_RL
		anim				anim_wpn_reload
		function			wpn_std_reload
	end

	action "empty"
		delayend				auto
		soundset			DRY_OICW	
		anim				anim_wpn_empty
		function			wpn_std_empty
	end

	action "switchto"
		soundset		GF_HKG3A_ST
		delaystart		1
		delayend		1
		anim				anim_wpn_switchto
		function			wpn_std_switchto
	end

	action "switchfrom"
		soundset		GF_HKG3A_SF
		delaystart		1
		delayend		1
		anim				anim_wpn_switchfrom
		function			wpn_std_switchfrom
	end

	action "switchrank"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchrank
		function			wpn_std_switchrank
	end
end

weapon "WPN_G3"
	category 3
	rank     19
	statid 	 319
	flags teamsabre

	charfilter cqb
	charfilter gunner
	charfilter medic

	round_type		"AMMO_G3_762MM"
	clipsize		20
	startrounds		0
	error_hip	.1
	error_up  	.058
	targetpitchmax  85				
	targetpitchmin  85				
	targetyawrange  120				
	ammoclass		CLASS_556MM	1
	clipslot		1
	launchuserpoint bullet

	flags Sighted
	flags Primary

	sights  G3_sgt2.tga		462 385 563 457 blend
	sights  G3_sgt.tga		200 295 823 824	blend
	
	

	crosshair coma20mm.tga
	hudicon H_g3s.tga
	hudclipgfx 	 0  0		H_clip.tga			
	hudrndgfx	 7  0 6 0 1	H_round.tga	    		

	animadm G3_1st

	gfx1 G3_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 G3_3rd
	pos		0.0		0.0		-200.0				0.0		0.4		1.0
	TPOS	-15.0		24.759	-184.423		0.0		0.4		0.0

	action "idle"
		delayend		  auto
		anim		  anim_wpn_idle
		function      wpn_std_idle
	end	

	action "emptyidle"
		delayend		  auto
		anim		  anim_wpn_idle
		function      wpn_std_idle
	end	

	action "fire"
		delayend			6	
		soundsetend			GS_HKG3A
		anim				anim_wpn_fire
		function			wpn_std_fire
		particle			Effect_CAR15MF
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			0
		anim				anim_wpn_recoil
		function			wpn_std_recoil
		particle			Effect_CAR15Cas
		particleuserpoint	bcasing
	end

	action "reload"
		delaystart			100
		delayend			auto
		soundset			GF_HKG3A_RL
		anim				anim_wpn_reload
		function			wpn_std_reload
	end

	action "empty"
		delayend				auto
		soundset			DRY_OICW	
		anim				anim_wpn_empty
		function			wpn_std_empty
	end

	action "switchto"
		soundset			GF_HKG3A_ST
		delaystart		1
		delayend		1
		anim				anim_wpn_switchto
		function			wpn_std_switchto
	end

	action "switchfrom"
		soundset				GF_HKG3A_SF
		delaystart		1
		delayend		1
		anim				anim_wpn_switchfrom
		function			wpn_std_switchfrom
	end

	action "switchrank"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchrank
		function			wpn_std_switchrank
	end
end




weapon "WPN_G36AUTO"
	category 3
	rank     20
	statid 320
	flags teamsabre

	charfilter cqb
	charfilter gunner
	charfilter medic

	loadout_selectable	1	
	loadout_subclasses	1	

	loadout_menu_icon	G36.tga
	loadout_menu_textid	WEAP_SHORT_G36
	loadout_menu_ttdesc WEAP_DESC_G36
	weapon_class	primary

	round_type		"AMMO_G36_556MM"
	clipsize		30
	startrounds		540
	classrounds		medic 210
	classrounds		gunner 600
	classrounds		cqb 330
	error_hip	.1	
	error_up  	.033  
	targetpitchmax  22				
	targetpitchmin  50				
	targetyawrange  120				
	ammoclass		CLASS_556MM	1
	clipslot		1
	launchuserpoint bullet

	flags auto
	flags Sighted

	SIGHTS	G36SGT.TGA		64	72	968	1114	blend
	SIGHTS	DOT_RED2.tga		508	380	516	388	blend scale
	SIGHTS	DOT_RED1.tga		508	380	516	388	add	scale

	crosshair coma20mm.tga
	hudicon H_g36a.tga
	hudclipgfx 	 0  0		H_clip.tga			
	hudrndgfx	 4  0 4 0 1	H_round.tga	    

	animadm g36_1st

	gfx1 g36_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 G36_3rd
	POS		-8.064	18.055	-206.182	0.0	1.0	0.5
	TPOS	-29.907	36.613	-196.443	0.0	0.0	0.0

	action "idle"
		delayend				auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "emptyidle"
		delayend				auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	


	action "fire"
		delayend				4
		soundsetend			GS_HKG36
		anim				anim_wpn_fire
		function			wpn_std_fire
		particle			Effect_CAR15MF
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			0
		anim				anim_wpn_recoil
		function			wpn_std_recoil
		particle			Effect_CAR15Cas
		particleuserpoint	bcasing
	end

	action "reload"
		delaystart			100
		delayend			auto
		soundset			GF_HKG36_RL
		anim				anim_wpn_reload
		function			wpn_std_reload
	end

	action "empty"
		delayend				auto
		soundset			DRY_OICW	
		anim				anim_wpn_empty
		function			wpn_std_empty
	end

	action "switchto"
		soundset		GF_HKG36_ST
		delaystart		1
		delayend		1
		anim				anim_wpn_switchto
		function			wpn_std_switchto
	end

	action "switchfrom"
		soundset		GF_HKG36_SF
		delaystart		1
		delayend		1
		anim				anim_wpn_switchfrom
		function			wpn_std_switchfrom
	end

	action "switchrank"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchrank
		function			wpn_std_switchrank
	end
end

weapon "WPN_G36"
	category 3
	rank     21
	statid 	 321
	flags teamsabre

	charfilter cqb
	charfilter medic
	//charfilter gunner

	round_type		"AMMO_G36_556MM"
	clipsize		30
	startrounds		0
	error_hip	.1 
	error_up  	.033 
	targetpitchmax  85				
	targetpitchmin  85				
	targetyawrange  120				
	ammoclass		CLASS_556MM	1
	clipslot		1
	launchuserpoint bullet

	flags Scoped
	flags Primary
	scope_max_mag 3
	scope_min_mag 4
	
	sights  g36aim.tga   112  0 889 768 blend
	sights  g36gls.tga   112  0 896 774 multiplyat
	sights  reddot1.tga    496  368 527 399 add		scale

	crosshair coma20mm.tga
	hudicon H_g36s.tga
	hudclipgfx 	 0  0		H_clip.tga			
	hudrndgfx	 4  0 4 0 1	H_round.tga	    

	animadm g36_1st

	gfx1 g36_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 G36_3rd
	POS		-8.064	18.055	-206.182	0.0	1.0	0.5
	TPOS	-34.223	36.613	-186.900	0.0	0.0	0.0


	action "idle"
		delayend		  auto
		anim		  anim_wpn_idle
		function      wpn_std_idle
	end	

	action "emptyidle"
		delayend		  auto
		anim		  anim_wpn_idle
		function      wpn_std_idle
	end	

	action "fire"
		delayend				4
		soundsetend			GS_HKG36
		anim				anim_wpn_fire
		function			wpn_std_fire
		particle			Effect_CAR15MF
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			0
		anim				anim_wpn_recoil
		function			wpn_std_recoil
		particle			Effect_CAR15Cas
		particleuserpoint	bcasing
	end

	action "reload"
		delaystart			100
		delayend			auto
		soundset			GF_HKG36_RL
		anim				anim_wpn_reload
		function			wpn_std_reload
	end

	action "empty"
		delayend				auto
		soundset			DRY_OICW	
		anim				anim_wpn_empty
		function			wpn_std_empty
	end

	action "switchto"
		soundset			GF_HKG36_ST
		delaystart		1
		delayend		1
		anim				anim_wpn_switchto
		function			wpn_std_switchto
	end

	action "switchfrom"
		soundset				GF_HKG36_SF
		delaystart		1
		delayend		1
		anim				anim_wpn_switchfrom
		function			wpn_std_switchfrom
	end

	action "switchrank"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchrank
		function			wpn_std_switchrank
	end
end





weapon "WPN_PSG1" //SVD
	category 3
	rank     22
	statid 322
	flags teamsabre


	charfilter sniper

	flags Sniper

	loadout_selectable	1	
	loadout_subclasses	0	

	loadout_menu_icon	PSG1.tga
	loadout_menu_textid	WEAP_SHORT_PSG1
	loadout_menu_ttdesc WEAP_DESC_PSG1
	weapon_class	primary

	round_type		"AMMO_DRAGUNOV_mm"
	clipsize		10
	startrounds		200
	error_hip	.5 
	error_up  	.025
	targetpitchmax  85				
	targetpitchmin  85				
	targetyawrange  120				
	ammoclass		CLASS_762HPBT	1
	launchuserpoint bullet

	flags Scoped
	scope_max_zero 10 100 200
	scope_max_mag	4

	crosshair coma20mm.tga
	hudicon H_PSG1a.tga
	hudclipgfx 	 0  0		H_clip.tga			
	hudrndgfx	 7  0 6 0 1	H_round.tga	    

	animadm SVD_1st
//	animadm psg1_1st

	gfx1 SVD_1st
//	gfx1 psg1_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 Dgnv_3RD
  	pos  28.097	10.884	-215.492	0.0	0.25	0.0
	tpos -9.518	39.448	-203.096	0.0	359.3	0.0

	action "idle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "emptyidle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "fire"
		delayend			13
		soundsetend			GS_PSG1
		anim				anim_wpn_fire
		function			wpn_std_fire
		particle			Effect_M21MF
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			0		
		//anim				anim_wpn_recoil
		function			wpn_std_recoil
		particle			Effect_M21Cas
		particleuserpoint	bcasing
	end

	action "reload"
		delaystart			90
		delayend			auto
		soundset			GF_PSG1_RL
		anim				anim_wpn_reload
		function			wpn_std_reload
	end

	action "empty"
		delayend				auto
		soundset			DRY_SNIPE	
		anim				anim_wpn_empty
		function			wpn_std_empty
	end

	action "switchto"
		soundset			GF_PSG1_ST
		delaystart			1
		delayend			1
		anim				anim_wpn_switchto
		function			wpn_std_switchto
	end

	action "switchfrom"
		soundset			GF_PSG1_SF
		delaystart		1
		delayend		1
		anim				anim_wpn_switchfrom
		function			wpn_std_switchfrom
	end

	action "switchrank"
		delaystart		27
		delayend		1
		anim				anim_wpn_switchrank
		function			wpn_std_switchrank
	end
end








weapon "WPN_GRENADEFB" 
	category 4
	rank     0
	statid 400

	charfilter cqb
	charfilter medic
	charfilter sniper
	//charfilter gunner

	loadout_selectable	1	
	loadout_subclasses	0	

	loadout_menu_icon	tbd.tga
	loadout_menu_textid	WEAP_SHORT_GRENADE_FLASH
	weapon_class	grenade

	flags	NoClipsNoDraw
	flags	Underwater
	flags	OkWhileJumping

	round_type		"GRENADEFB"
	clipsize		1
	startrounds		5
	classrounds		medic 5
	classrounds		sniper 2
	classrounds		cqb 3
	error_hip	0 
	error_up  	0 
	targetpitchmax  85				
	targetpitchmin  85				
	targetyawrange  120				
	ammoclass		CLASS_GRENADEFB	1

	attack_anim	 2		
	special_hold 1		

	launchuserpoint bullet

	crosshair coma20mm.tga
	hudicon H_flash.tga
	
	animadm Flsh_1st

	gfx1 Flsh_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 Flsh_3RD
  	pos  -33 8 -177 0 0 0

	action "idle"
		delayend		  auto
		anim		  anim_wpn_idle
		function      wpn_std_idle
	end	

	action "emptyidle"
		delaystart			auto
		anim				anim_wpn_empty_idle
		function			wpn_std_emptyidle
	end	

	action "fire"
		delaystart			70

		delayend			auto
		soundset			GF_CNADE_THROW
		
		anim				anim_wpn_fire
		function			wpn_std_fire
	end

	action "recoil"
		delayend				auto
		anim				anim_wpn_recoil
		function			wpn_std_recoil
	end

	action "reload"
		delayend				auto
		anim				anim_wpn_reload
		function			wpn_std_reload
	end

	action "empty"
		soundset		DRY_CLAYSATCH
		delayend				auto  
		function			wpn_std_empty
	end

	action "switchto"
		soundset		GF_GNADE_ST
		delaystart		1
		delayend		1
		anim				anim_wpn_switchto
		function			wpn_std_switchto
	end

	action "switchfrom"
		soundset		GF_GNADE_ST
		delaystart		1
		delayend		1
		anim				anim_wpn_switchfrom
		function			wpn_std_switchfrom
	end

	action "switchrank"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchrank
		function			wpn_std_switchrank
	end
end

weapon "WPN_GRENADEHE"
	category 5
	rank     0
	statid 401

	charfilter cqb
	//charfilter medic
	charfilter sniper
	charfilter gunner

	loadout_selectable	1	
	loadout_subclasses	0	

	loadout_menu_icon	tbd.tga
	loadout_menu_textid	WEAP_SHORT_GRENADE_FRAG
	weapon_class	grenade

	flags	NoClipsNoDraw
	flags	Underwater
	flags	OkWhileJumping

	round_type		"GRENADEHE"
	clipsize		1
	startrounds		5
	//classrounds		medic 1
	classrounds		sniper 2
	classrounds		cqb 3
	classrounds		gunner 2
	error_hip	0 
	error_up  	0 
	targetpitchmax  85				
	targetpitchmin  85				
	targetyawrange  120				
	ammoclass		CLASS_GRENADEHE	1

	crosshair coma20mm.tga
	hudicon H_frag.tga
	

	launchuserpoint bullet

	attack_anim	 2		
	special_hold 1		

	animadm frag_1st

	gfx1 Frag_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 Frag_3RD
  	pos  -33 8 -177 0 0 0

	action "idle"
		delayend		  auto
		anim		  anim_wpn_idle
		function      wpn_std_idle
	end	

	action "emptyidle"
		delaystart			auto
		anim				anim_wpn_empty_idle
		function			wpn_std_emptyidle
	end	

	action "fire"
		delaystart			80
		delayend			auto
		soundset			GF_GNADE_THROW
		anim				anim_wpn_fire
		function			wpn_std_fire
	end

	action "recoil"
		delayend				auto
		anim				anim_wpn_recoil
		function			wpn_std_recoil
	end

	action "reload"
		delayend				auto
		anim				anim_wpn_reload
		function			wpn_std_reload
	end

	action "empty"
		soundset		DRY_CLAYSATCH
		delayend				auto 
		function			wpn_std_empty
	end

	action "switchto"
		soundset		GF_GNADE_ST
		delaystart		1
		delayend		1
		anim				anim_wpn_switchto
		function			wpn_std_switchto
	end

	action "switchfrom"
		soundset		GF_GNADE_ST
		delaystart		1
		delayend		1
		anim				anim_wpn_switchfrom
		function			wpn_std_switchfrom
	end

	action "switchrank"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchrank
		function			wpn_std_switchrank
	end
end

weapon "WPN_GRENADESM" 
	category 6
	rank     0
	statid 402

	charfilter cqb
	charfilter medic
	charfilter sniper
	charfilter gunner

	loadout_selectable	1	
	loadout_subclasses	1	

	loadout_menu_icon	tbd.tga
	loadout_menu_textid	WEAP_SHORT_GRENADE_SMOKE
	weapon_class	grenade

	flags	NoClipsNoDraw
	flags	Underwater
	flags	OkWhileJumping

	round_type		"GRENADESM"
	clipsize		1
	startrounds		3
	error_hip	0 
	error_up  	0 
	targetpitchmax  85				
	targetpitchmin  85				
	targetyawrange  120				
	ammoclass		CLASS_GRENADESM	1

	launchuserpoint bullet

	attack_anim	 2		
	special_hold 1		

	crosshair coma20mm.tga
	hudicon H_smoke.tga
	
	animadm smok_1st

	gfx1 smok_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 smok_3RD
  	pos  -33 8 -177 0 0 0

	action "idle"
		delayend		  auto
		anim		  anim_wpn_idle
		function      wpn_std_idle
	end	

	action "emptyidle"
		delaystart			auto
		anim				anim_wpn_empty_idle
		function			wpn_std_emptyidle
	end	

	action "fire"
		delayend				auto
		delaystart				65
		soundset			GF_CNADE_THROW
		anim				anim_wpn_fire
		function			wpn_std_fire
	end

	action "recoil"
		delayend				auto
		anim				anim_wpn_recoil
		function			wpn_std_recoil
	end

	action "reload"
		delayend				auto
		anim				anim_wpn_reload
		function			wpn_std_reload
	end

	action "empty"
		soundset		DRY_CLAYSATCH
		delayend				auto 
		function			wpn_std_empty
	end

	action "switchto"
		soundset		GF_GNADE_ST
		delaystart		1
		delayend		1
		anim				anim_wpn_switchto
		function			wpn_std_switchto
	end

	action "switchfrom"
		soundset		GF_GNADE_ST
		delaystart		1
		delayend		1
		anim				anim_wpn_switchfrom
		function			wpn_std_switchfrom
	end

	action "switchrank"
		delaystart		1
		delayend		1
		anim				anim_wpn_switchrank
		function			wpn_std_switchrank
	end
end


weapon "WPN_SWORD"
	category 6
	rank     1
	statid 203

	charfilter cqb
	charfilter medic
	charfilter sniper
	charfilter gunner

	round_type  "sword01"
	clipsize    -1
	startrounds -1
	error_hip	0 
	error_up  	0 
	targetpitchmax  22				
	targetpitchmin  50				
	targetyawrange  15				
	run_anim 1

	launchuserpoint bullet

	animadm det_1st
	flags	Underwater
	flags	OkWhileJumping

	hudicon h_deton.tga

	gfx1 det_1st  
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 det_3rd 
	pos  13 -7 -205 0 0 0

	action "idle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "emptyidle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "fire"
		soundsetend	CLICK_SATCHEL	
		delaystart		30
		delayend      auto
		anim		  anim_wpn_fire
		function      wpn_std_fire
	end

	action "recoil"
		delayend      auto			
		anim		  anim_wpn_recoil
		function      wpn_std_recoil
	end

	action "reload"
		delayend         auto
		anim		  anim_wpn_reload
		function      wpn_std_reload
	end

	action "empty"
		soundset	DRY_CLAYSATCH  
		delayend         auto
		function      wpn_std_empty
	end

	action "switchto"
		delaystart		1
		delayend		1
		function      wpn_std_switchto
	end

	action "switchfrom"
		delaystart		1
		delayend		1
		function      wpn_std_switchfrom
	end
end


weapon "WPN_MEDPACK"
	category 9
	rank     0
	statid 700

	charfilter medic

	round_type  "medpack"
	clipsize    -1
	startrounds -1
	error_hip	0 
	error_up  	0 
	targetpitchmax  85				
	targetpitchmin  85				
	targetyawrange  120				
	launchuserpoint bullet
	run_anim 1

	flags	Underwater
	crosshair coma20mm.tga
	hudicon H_medpak.tga

	animadm medp_1st

	gfx1 medp_1st
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 medp_3rd 
	pos  4 -5 -186 0 0 0

	action "idle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "emptyidle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "fire"
		delayend		  auto
		soundsetend	  MEDPAK_USE
		anim		  anim_wpn_fire
		function      wpn_std_fire
	end

	action "recoil"
		delayend		  auto
		anim		  anim_wpn_recoil
		function      wpn_std_recoil
	end

	action "reload"
		delayend		  auto
		anim		  anim_wpn_reload
		function      wpn_std_reload
	end

	action "empty"
		soundset	DRY_CLAYSATCH
		delayend		  auto
		anim		  anim_wpn_empty
		function      wpn_std_empty
	end

	action "switchto"
		soundset	GF_SATCHEL_ST
		delaystart		1
		delayend		1
		anim		  anim_wpn_switchto
		function      wpn_std_switchto
	end

	action "switchfrom"
		soundset	GF_SATCHEL_SF
		delaystart		1
		delayend		1
		anim		  anim_wpn_switchfrom
		function      wpn_std_switchfrom
	end

	action "switchrank"
		delaystart		1
		delayend		1
		anim		  anim_wpn_switchrank
		function      wpn_std_switchrank
	end
end


weapon "WPN_SATCHEL_CHARGE"
	category 7
	rank     0
	statid 500

	charfilter cqb
	//charfilter gunner
	charfilter sniper

	loadout_selectable	1	
	loadout_subclasses	1	

	loadout_menu_icon	tbd.tga
	loadout_menu_textid	WEAP_SHORT_SATCHEL
	loadout_menu_ttdesc WEAP_DESC_SATCHEL
	weapon_class	accessory

	round_type  "satchel"
	clipsize    1
	startrounds 3
	classrounds		sniper 2
	//classrounds		gunner 1
	classrounds		cqb 3
	error_hip	0 
	error_up  	0 
	targetpitchmax  22				
	targetpitchmin  50				
	targetyawrange  15				

	animadm stch_1st

	flags	NoClipsNoDraw
	flags	Underwater
	flags	OkWhileJumping

	hudicon h_satchl.tga

	gfx1 stch_1st  
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 stch_3rd 
	pos  16 -34 -205 0 0 0

	ammoclass	CLASS_SATCHEL 1

	action "idle"
		delayend		  auto
		anim		  anim_wpn_idle
		function      wpn_std_idle
	end	

	action "emptyidle"
		delaystart			auto
		anim				anim_wpn_empty_idle
		function			wpn_std_emptyidle
	end	

	action "fire"
		soundsetend	  MEDPAK_USE
		delaystart		30
		delayend         auto
		anim		  anim_wpn_fire
		function      wpn_std_fire
	end

	action "recoil"
		delayend      auto			
		anim		  anim_wpn_recoil
		function      wpn_std_recoil
	end

	action "reload"
		delaystart         auto
		anim		  anim_wpn_reload
		function      wpn_std_reload
	end

	action "empty"
		soundset	DRY_CLAYSATCH 
		delaystart         auto
		function      wpn_std_empty
	end

	action "switchto"
		soundset	GF_SATCHEL_ST
		delaystart		1
		delayend		1
		function      wpn_std_switchto
	end

	action "switchfrom"
		soundset	GF_SATCHEL_SF
		delaystart		1
		delayend		1
		function      wpn_std_switchfrom
	end
end


weapon "WPN_SATCHEL_DETONATOR"
	category 8
	rank     0
	statid 600

	charfilter cqb
	//charfilter gunner
	charfilter sniper

	round_type  "detonator"
	clipsize    -1
	startrounds -1
	error_hip	0 
	error_up  	0 
	targetpitchmax  22				
	targetpitchmin  50				
	targetyawrange  15				
	run_anim 1

	launchuserpoint bullet

	animadm det_1st
	flags	Underwater
	flags	OkWhileJumping

	hudicon h_deton.tga

	gfx1 det_1st  
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 det_3rd 
	pos  13 -7 -205 0 0 0

	action "idle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "emptyidle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "fire"
		soundsetend	CLICK_SATCHEL	
		delaystart		30
		delayend      auto
		anim		  anim_wpn_fire
		function      wpn_std_fire
	end

	action "recoil"
		delayend      auto			
		anim		  anim_wpn_recoil
		function      wpn_std_recoil
	end

	action "reload"
		delayend         auto
		anim		  anim_wpn_reload
		function      wpn_std_reload
	end

	action "empty"
		soundset	DRY_CLAYSATCH  
		delayend         auto
		function      wpn_std_empty
	end

	action "switchto"
		delaystart		1
		delayend		1
		function      wpn_std_switchto
	end

	action "switchfrom"
		delaystart		1
		delayend		1
		function      wpn_std_switchfrom
	end
end


weapon "WPN_CLAYMORE"
	category 7
	rank     1
	statid 501

	charfilter cqb
	charfilter sniper

	loadout_selectable	1	
	loadout_subclasses	0	

	loadout_menu_icon	tbd.tga
	loadout_menu_textid	WEAP_SHORT_CLAYMORE
	loadout_menu_ttdesc WEAP_DESC_CLAYMORE
	weapon_class	accessory

	round_type  "claymore"
	clipsize    1
	startrounds 4
	classrounds		sniper 4
	classrounds		cqb 1
	error_hip	0 
	error_up  	0 
	targetpitchmax  22				
	targetpitchmin  50				
	targetyawrange  15				

	animadm stch_1st

	flags	NoClipsNoDraw
	flags	OkWhileJumping

	hudicon h_clymor.tga

	gfx1 clym_1st  
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 clym_3rd 
	pos  16 -34 -205 0 0 0

	ammoclass	CLASS_CLAYMORE 1

	action "idle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "emptyidle"
		delaystart			auto
		anim				anim_wpn_empty_idle
		function			wpn_std_emptyidle
	end	

	action "fire"
		delaystart		30
		delayend      auto
		anim		  anim_wpn_fire
		function      wpn_std_fire
	end

	action "recoil"
		delayend      auto		
		anim		  anim_wpn_recoil
		function      wpn_std_recoil
	end

	action "reload"
		delayend         auto
		anim		  anim_wpn_reload
		function      wpn_std_reload
	end

	action "empty"
		soundset	DRY_CLAYSATCH
		delayend      auto
		function      wpn_std_empty
	end

	action "switchto"
		soundset	GF_SATCHEL_ST
		delaystart		1
		delayend		1
		function      wpn_std_switchto
	end

	action "switchfrom"
		soundset	GF_SATCHEL_SF
		delaystart		1
		delayend		1
		function      wpn_std_switchfrom
	end
end


weapon "WPN_AT4"
	category 7
	rank     2
	statid 502

	charfilter gunner

	loadout_selectable	1	
	loadout_subclasses	0	

	loadout_menu_icon	tbd.tga
	loadout_menu_textid	WEAP_SHORT_AT4
	loadout_menu_ttdesc WEAP_DESC_AT4
	weapon_class	accessory

	round_type  "ROCKETAT4"
	clipsize    1
	startrounds 3
	error_hip	0 
	error_up  	0 
	targetpitchmax  22				
	targetpitchmin  50				
	targetyawrange  15				

	launchuserpoint bullet

	ammoclass	CLASS_AT4	1

	flags Sighted

	sights  At4irnA.tga   373  134 1024 782 blend
	sights  At4irnB.tga   447  356 576 485 blend

	animadm at4_1st
	crosshair coma20mm.tga

	hudicon h_at4.tga

	gfx1 at4_1st   
	gfx1a arms
	gfx1b armsb
	gfx1_sa armsc
	gfx1_sb armscb
	gfx3 at4_3rd 
	pos  -7 -13 -200 0 0 0
	tpos  -37 3 -192 0 0 0

	action "idle"
		delayend			auto
		anim				anim_wpn_idle
		function			wpn_std_idle
	end	

	action "emptyidle"
		delaystart			auto
		anim				anim_wpn_empty_idle
		function			wpn_std_emptyidle
	end	

	action "fire"
		delaystart		1
		delayend      auto
		soundsetend	GS_AT4
		anim		  anim_wpn_fire
		function      wpn_std_fire
		particle			Effect_AT4MF
		particleuserpoint	mflash01
	end

	action "recoil"
		delaystart		auto
		anim		  anim_wpn_recoil
		function      wpn_std_recoil
	end

	action "reload"
		delaystart    100
		anim		  anim_wpn_reload
		function      wpn_std_reload
	end

	action "empty"
		delaystart		auto
		soundset	DRY_AT4
		function      wpn_std_empty
	end

	action "switchto"
		soundset	GF_AT4_ST
		delaystart		1
		delayend		1
		function      wpn_std_switchto
	end

	action "switchfrom"
		soundset	GF_AT4_SF
		delaystart		1
		delayend		1
		function      wpn_std_switchfrom
	end
end




weapon "WPN_EMPLCD50"
	category 10
	rank     3
	statid 903

	round_type  "50cal"
	clipsize    -1
	startrounds 500
	error_hip	.025 
	error_up  	.025 
	targetpitchmax  15				
	targetpitchmin  45				
	targetyawrange  180				

	launchuserpoint camera 
	gfx1 b50b_1st
	gfx3 EM50cal

	attachtextid attach_50cal

	animadm b50_1st

	crosshair 50cal.tga
	hudicon h_50cal.tga

	flags auto
	flags Emplaced

	pos  -66 0 -157 0 0 0

	
	

	action "idle"
		function      wpn_std_idle
		anim		  anim_wpn_idle
	end	

	action "fire"
		anim				anim_wpn_fire
		soundsetend			GS_50CALN6
		delayend			auto 
		function			wpn_std_fire
		particle			Effect_MiniMuz
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			1
		soundsetend			GF_MGUN_CASING
		function			wpn_std_recoil
		particle			Effect_50Calcasing
		particleuserpoint	bcasing
	end

	action "reload"
		delayend         0
		function      wpn_std_reload
	end

	action "empty"
		soundset		DRY_MG  
		delayend         0
		function      wpn_std_empty
	end

	action "switchto"
		delaystart		1
		delayend		1
		function      wpn_std_switchto
	end

	action "switchfrom"
		delaystart		1
		delayend		1
		function      wpn_std_switchfrom
	end
end

weapon "WPN_EMPLCDMINI"
	category 10
	rank     4
	statid 904

	round_type  "minirnds"
	clipsize    -1
	startrounds 500
	error_hip	0.15 
	error_up  	0.125 
	targetpitchmax  75				
	targetpitchmin  12				
	targetyawrange  75				

	launchuserpoint camera 
	gfx3 minigun

	attachtextid attach_minigun

	crosshair 50cal.tga
	hudicon h_minign.tga

	flags auto
	flags Emplaced

	pos  -6 -14 -205 0 0 0

	soundhead GS_MINIHEAD
	soundfireloop LP_GS_MINIGUN
	soundtrailoff GS_MINITAIL


	action "idle"
		function      wpn_std_idle
		anim		  anim_wpn_idle
	end	

	action "fire"
		soundsetend   GF_MGUN_CASING
		delayend	  0
		function      wpn_std_fire
		particle	  Effect_MiniMuz
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend	  0
		function      wpn_std_recoil
		particle	  Effect_50Calcasing
		particleuserpoint	bcasing
	end

	action "reload"
		delayend         0
		function      wpn_std_reload
	end

	action "empty"
		soundset		DRY_MINI  
		delayend         0
		function      wpn_std_empty
	end

	action "switchto"
		delaystart		1
		delayend		1
		function      wpn_std_switchto
	end

	action "switchfrom"
		delaystart		1
		delayend		1
		function      wpn_std_switchfrom
	end
end

weapon "WPN_EMPLCDGRND"
	category 10
	rank     5
	statid 905

	round_type  "MK19nade"
	clipsize    -1
	startrounds -1
	error_hip	1.0 
	error_up  	1.0 
	targetpitchmax  45				
	targetpitchmin  45				
	targetyawrange  135				

	launchuserpoint camera 
	gfx3 MK19
	crosshair coma20mm.tga
	hudicon h_mk19.tga

	attachtextid attach_mk19

	flags auto
	flags Emplaced

	pos  -6 -14 -205 0 0 0

	
	

	action "idle"
		function      wpn_std_idle
		anim		  anim_wpn_idle
	end	

	action "fire"
		soundsetend			GS_EMP_GLAUNCH
		delayend			1
		function			wpn_std_fire
		particle			Effect_MK19Muz
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			30
		function			wpn_std_recoil
		particle			Effect_Grencasing
		particleuserpoint	bcasing
	end

	action "reload"
		delayend			300
		function			wpn_std_reload
	end

	action "empty"
		soundset		DRY_AT4 
		delayend			0
		function			wpn_std_empty
	end

	action "switchto"
		delaystart		1
		delayend		1
		function      wpn_std_switchto
	end

	action "switchfrom"
		delaystart		1
		delayend		1
		function      wpn_std_switchfrom
	end
end


weapon "WPN_EMP50ETEK"   
	category 10
	rank     7
	statid 907

	round_type  "50cal"
	clipsize    -1
	startrounds 500
	error_hip	.025 
	error_up  	.025 
	targetpitchmax  45				
	targetpitchmin  45				
	targetyawrange  180				

	launchuserpoint camera 

	animadm b50_1st
	gfx1 b50_1st
	gfx3 E50ETEK

	attachtextid attach_50cal

	crosshair 50cal.tga
	hudicon h_50cal.tga

	flags auto
	flags Emplaced

	pos  -58 0 -161 0 0 0


	
	

	action "idle"
		function      wpn_std_idle
		anim		  anim_wpn_idle
	end	

	action "fire"
		soundsetend			GS_50CALN6
		delayend			auto 
		anim				anim_wpn_fire
		particle			Effect_MiniMuz
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			1
		function			wpn_std_recoil
		particle			Effect_50Calcasing
		particleuserpoint	bcasing
	end

	action "reload"
		delayend         0
		function		wpn_std_reload
	end

	action "empty"
		soundset		DRY_MG  
		delayend         0
		function      wpn_std_empty
	end

	action "switchto"
		delaystart		1
		delayend		1
		function      wpn_std_switchto
	end

	action "switchfrom"
		delaystart		1
		delayend		1
		function      wpn_std_switchfrom
	end
end

weapon "WPN_EMP50TRI"
	category 10
	rank     8
	statid 908

	round_type  "50cal"
	clipsize    -1
	startrounds 500
	error_hip	.7 
	error_up  	.7 
	targetpitchmax  45				
	targetpitchmin  45				
	targetyawrange  180				

	launchuserpoint camera 

	animadm b50_1st
	gfx1 b50_1st
	gfx3 E50tripd
	crosshair 50cal.tga

	attachtextid attach_50cal
	hudicon h_50cal.tga

	flags auto
	flags Emplaced

	pos  -58 0 -161 0 0 0


	
	

	action "idle"
		function      wpn_std_idle
		anim		  anim_wpn_idle
	end	

	action "fire"
		anim				anim_wpn_fire
		soundsetend			GS_50CALN6
		delayend			auto 
		function			wpn_std_fire
		particle			Effect_MiniMuz
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			1
		function			wpn_std_recoil
		particle			Effect_50Calcasing
		particleuserpoint	bcasing
	end

	action "reload"
		delayend         0
		function      wpn_std_reload
	end

	action "empty"
		soundset		DRY_MG  
		delayend         0
		function      wpn_std_empty
	end

	action "switchto"
		delaystart		1
		delayend		1
		function      wpn_std_switchto
	end

	action "switchfrom"
		delaystart		1
		delayend		1
		function      wpn_std_switchfrom
	end
end


weapon "WPN_EMcannon"
	category 10
	rank     9
	statid 909

	round_type  "Rclsrnd"
	clipsize    -1
	startrounds 500
	error_hip	1.4 
	error_up  	1.4 
	targetpitchmax  45				
	targetpitchmin  45				
	targetyawrange  180				

	launchuserpoint camera 

	gfx3 EMcannon

	crosshair 50cal.tga
	hudicon h_minigun.tga

	attachtextid attach_emcannon

	flags auto
	flags Emplaced

	pos  -16 0 -155 0 0 0

	action "idle"
		function      wpn_std_idle
		anim		  anim_wpn_idle
	end	

	action "fire"
		anim				anim_wpn_fire
		soundsetend			GS_EMCANNON
		delayend			auto 
		function			wpn_std_fire
		particle			Effect_MiniMuz
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			120
		function			wpn_std_recoil
		particle			Effect_50Calcasing
		particleuserpoint	bcasing
	end

	action "reload"
		delayend         0
		function		wpn_std_reload
	end

	action "empty"
		soundset		DRY_MG  
		delayend         0
		function		wpn_std_empty
	end

	action "switchto"
		delaystart		1
		delayend		1
		function		wpn_std_switchto
	end

	action "switchfrom"
		delaystart		1
		delayend		1
		function      wpn_std_switchfrom
	end
end


weapon "WPN_UG50cal"
	category 10
	rank     10
	statid 910

	round_type  "50cal"
	clipsize    -1
	startrounds 500
	error_hip	.025 
	error_up  	.025 
	targetpitchmax  45				
	targetpitchmin  45				
	targetyawrange  180				

	launchuserpoint camera 
	
	gfx1 b50_1st
	gfx3 UG50cal
	animadm b50_1st
	crosshair 50cal.tga

	attachtextid attach_50cal
	hudicon h_50cal.tga

	flags auto
	flags Emplaced

	pos  -58 0 -161 0 0 0


	
	

	action "idle"
		function      wpn_std_idle
		anim		  anim_wpn_idle
	end	

	action "fire"
		anim				anim_wpn_fire
		soundsetend			GS_50CALN6
		delayend			auto 
		function			wpn_std_fire
		particle			Effect_MiniMuz
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			1
		function			wpn_std_recoil
		particle			Effect_50Calcasing
		particleuserpoint	bcasing
	end

	action "reload"
		delayend         0
		function      wpn_std_reload
	end

	action "empty"
		soundset		DRY_MG  
		delayend         0
		function      wpn_std_empty
	end

	action "switchto"
		delaystart		1
		delayend		1
		function      wpn_std_switchto
	end

	action "switchfrom"
		delaystart		1
		delayend		1
		function      wpn_std_switchfrom
	end
end

weapon "WPN_EMPLCD50NA"			
	category 10
	rank     11
	statid 911

	round_type  "50cal"
	clipsize    -1
	startrounds 500
	error_hip	.025 
	error_up  	.025 
	targetpitchmax  15				
	targetpitchmin  45				
	targetyawrange  180				

	launchuserpoint camera 
	gfx1 b50_1st
	gfx3 H50cal

	attachtextid attach_50cal
	animadm b50_1st

	crosshair 50cal.tga
	hudicon h_50cal.tga

	flags auto
	flags Emplaced

	pos  -66 0 -157 0 0 0

	
	

	action "idle"
		function      wpn_std_idle
		anim		  anim_wpn_idle
	end	

	action "fire"
		anim				anim_wpn_fire
		soundsetend			GS_50CALN6
		delayend			auto 
		function			wpn_std_fire
		particle			Effect_MiniMuz
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			1
		soundsetend			GF_MGUN_CASING
		function			wpn_std_recoil
		particle			Effect_50Calcasing
		particleuserpoint	bcasing
	end

	action "reload"
		delayend         0
		function      wpn_std_reload
	end

	action "empty"
		soundset		DRY_MG  
		delayend         0
		function      wpn_std_empty
	end

	action "switchto"
		delaystart		1
		delayend		1
		function      wpn_std_switchto
	end

	action "switchfrom"
		delaystart		1
		delayend		1
		function      wpn_std_switchfrom
	end
end

weapon "WPN_EMP50TRI180"
	category 10
	rank     12
	statid 912

	round_type  "50cal"
	clipsize    -1
	startrounds 500
	error_hip	.7 
	error_up  	.7 
	targetpitchmax  45				
	targetpitchmin  45				
	targetyawrange  90				

	launchuserpoint camera 

	animadm b50_1st
	gfx1 b50_1st
	gfx3 E50tripd
	crosshair 50cal.tga

	attachtextid attach_50cal
	hudicon h_50cal.tga

	flags auto
	flags Emplaced

	pos  -58 0 -161 0 0 0


	
	

	action "idle"
		function      wpn_std_idle
		anim		  anim_wpn_idle
	end	

	action "fire"
		anim				anim_wpn_fire
		soundsetend			GS_50CALN6
		delayend			auto 
		function			wpn_std_fire
		particle			Effect_MiniMuz
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			1
		function			wpn_std_recoil
		particle			Effect_50Calcasing
		particleuserpoint	bcasing
	end

	action "reload"
		delayend         0
		function      wpn_std_reload
	end

	action "empty"
		soundset		DRY_MG  
		delayend         0
		function      wpn_std_empty
	end

	action "switchto"
		delaystart		1
		delayend		1
		function      wpn_std_switchto
	end

	action "switchfrom"
		delaystart		1
		delayend		1
		function      wpn_std_switchfrom
	end
end


weapon "WPN_WEAKAIMINI"
	category 10
	rank     13
	statid 913

	round_type  "wkminirnds"
	clipsize    -1
	startrounds 500
	error_hip	1.0 
	error_up  	1.0 
	targetpitchmax  75				
	targetpitchmin  12				
	targetyawrange  75				

	launchuserpoint camera 
	gfx3 minigun

	attachtextid attach_minigun

	crosshair 50cal.tga
	hudicon h_minign.tga

	flags auto
	flags Emplaced

	pos  -6 -14 -205 0 0 0

	soundhead GS_MINIHEAD
	soundfireloop LP_GS_MINIGUN
	soundtrailoff GS_MINITAIL


	action "idle"
		function      wpn_std_idle
		anim		  anim_wpn_idle
	end	

	action "fire"
		soundsetend   GF_MGUN_CASING
		delaystart    0
		delayend	  0
		function      wpn_std_fire
		particle	  Effect_MiniMuz
		particleuserpoint	mflash01
	end

	action "recoil"
		delaystart    0
		delayend	  7
		function      wpn_std_recoil
		particle	  Effect_50Calcasing
		particleuserpoint	bcasing
	end

	action "reload"
		delayend         0
		function      wpn_std_reload
	end

	action "empty"
		soundset		DRY_MINI  
		delayend         0
		function      wpn_std_empty
	end

	action "switchto"
		delaystart		1
		delayend		1
		function      wpn_std_switchto
	end

	action "switchfrom"
		delaystart		1
		delayend		1
		function      wpn_std_switchfrom
	end
end


weapon "WPN_EMP50VBL"   
	category 10
	rank     14
	statid 914

	round_type  "AMMO_M60_762MM"
	clipsize    -1
	startrounds 500
	error_hip	1.4  
	error_up  	0.7  
	targetpitchmax  45				
	targetpitchmin  45				
	targetyawrange  180				

	launchuserpoint mflash01 

	animadm b50_1st
	gfx1 b50_1st
	gfx3 VBLtur

	attachtextid attach_50cal

	crosshair 50cal.tga
	hudicon h_50cal.tga

	flags auto
	flags Emplaced

	pos  -58 0 -161 0 0 0


	
	

	action "idle"
		function      wpn_std_idle
		anim		  anim_wpn_idle
	end	

	action "fire"
		soundsetend			GS_50CALN6
		delayend			auto 
		anim				anim_wpn_fire
		particle			Effect_MiniMuz
		particleuserpoint	mflash01
	end

	action "recoil"
		delayend			1
		function			wpn_std_recoil
		particle			Effect_50Calcasing
		particleuserpoint	bcasing
	end

	action "reload"
		delayend         0
		function		wpn_std_reload
	end

	action "empty"
		soundset		DRY_MG  
		delayend         0
		function      wpn_std_empty
	end

	action "switchto"
		delaystart		1
		delayend		1
		function      wpn_std_switchto
	end

	action "switchfrom"
		delaystart		1
		delayend		1
		function      wpn_std_switchfrom
	end
end


