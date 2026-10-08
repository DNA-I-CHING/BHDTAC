// KEY:0x2A5A8EAD









ammo AT_NULL
	velocity 0
	max_age 0
	error 0
	bullet_mass 0
	drag 1

    ai_launch		NULL_SET 		

	effects_table
		move       none                		none          		0   
		obj        none   					imp_bullet_dirt   	15
		dirt       Effect_PistolDirt    	imp_bullet_dirt   	15
		grass      Effect_PistolGrass   	imp_bullet_grass  	15
		snow       Effect_PistolSnow    	imp_bullet_dirt   	1
		cement     Effect_PistolDirt    	imp_bullet_dirt   	15
		packeddirt Effect_PistolDirt    	imp_bullet_dirt   	15
		water      Effect_PistolWater  		imp_bullet_water  	5
		railroad   Effect_PistolMetal   	imp_bullet_metal  	15
		mud        Effect_PistolDirt     	imp_bullet_mud    	15
		ice        Effect_PistolSnow     	imp_bullet_mud    	15
		sand       Effect_PistolSand    	imp_bullet_sand   	15
		quicksand  Effect_PistolSand    	imp_bullet_sand   	15
		stone      Effect_PistolStone   	imp_bullet_rock  	15
		wood       Effect_PistolDirt    	imp_bullet_wood   	5
		metal      Effect_PistolMetal   	imp_bullet_metal  	15
		glass      Effect_PistolGlass      	imp_glass          	5
		cloth      Effect_PistolDirt   		IMP_BULLET_CLOTH 	3
		foliage    Effect_PistolGrass 		IMP_BULLET_FOLIAGE   	3
		hmetal     Effect_PistolMetal   	imp_bullet_armor  	15
		flesh      Effect_PistolBody   		imp_bullet_flesh  	3
		player		none					imp_bullet_flesh	10  
		zip			none					WSH_BULLET_BY		10	    
	end
end

ammo sword01
	frndlyTrcrID		1905   
	bullet_mass 1
	max_age 0.1     
	arm_age 0      
	velocity 1		
	error 0
	drag  1

	impact_damage 10
    
	//flag instantkillzone
	kztype rounds_kz_C4
	kz_damage 800
	kz_minradius 0.1
	kz_maxradius 0.25

    impact_AI_damage 3	
    kz_AI_damage    3 

	effects_table
		move       none						none				0
		obj        none   imp_20mm_dirt		15
		dirt       Effect_PistolDirt		imp_20mm_dirt	15
		grass      Effect_PistolGrass		imp_bullet_grass 15
		snow       Effect_PistolSnow		imp_20mm_dirt	1
		cement     Effect_PistolStone		imp_20mm_dirt	15
		packeddirt Effect_PistolDirt		imp_20mm_dirt	15
		water      Effect_PistolWater		imp_20mm_water	5
		railroad   Effect_PistolMetal		imp_20mm_metal	15
		mud        Effect_PistolDirt		imp_bullet_mud   15
		ice        Effect_PistolSnow		imp_bullet_mud   15
		sand       Effect_PistolSand		IMP_BULLET_SAND	15
		quicksand  Effect_PistolSand		IMP_BULLET_SAND	15
		stone      Effect_PistolStone		imp_20mm_rock	15
		wood       Effect_PistolDirt		imp_20mm_wood	5
		metal      Effect_PistolMetal		imp_20mm_metal	15
		glass      Effect_PistolGlass		imp_glass			5
		cloth      Effect_PistolDirt		IMP_20MM_CLOTH 3
		foliage    Effect_PistolGrass		imp_20mm_foliage 3
		hmetal     Effect_PistolMetal		imp_20mm_armor	15
		flesh      Effect_PistolBody		imp_20mm_flesh	3
		player		none					imp_20mm_flesh	10
		zip			none					wsh_shell_by	10
	end
end

ammo 20MM
	bullet_mass 1
	max_age 3     
	velocity 300	
	error 0
	drag  1
	scorch_id 1
	scar_type 1
	frndlyTrcrID 4405
	foeTrcrID	 4406
	impact_damage 16
    flag muzzle1  
    ai_launch		GS_20MM 	
	recoil		24

	Mf_Light 100

	kztype rounds_kz_Bullets
	kz_damage 8
	kz_minradius 2.0
	kz_maxradius 3.0

    impact_AI_damage 5	
    kz_AI_damage    3 

	effects_table
		move       none						none				0
		obj        none						imp_20mm_dirt		15
		dirt       Effect_PistolDirt		imp_20mm_dirt	15
		grass      Effect_PistolGrass		imp_bullet_grass 15
		snow       Effect_PistolSnow		imp_20mm_dirt	1
		cement     Effect_PistolStone		imp_20mm_dirt	15
		packeddirt Effect_PistolDirt		imp_20mm_dirt	15
		water      Effect_PistolWater		imp_20mm_water	5
		railroad   Effect_PistolMetal		imp_20mm_metal	15
		mud        Effect_PistolDirt		imp_bullet_mud   15
		ice        Effect_PistolSnow		imp_bullet_mud   15
		sand       Effect_PistolSand		IMP_BULLET_SAND	15
		quicksand  Effect_PistolSand		IMP_BULLET_SAND	15
		stone      Effect_PistolStone		imp_20mm_rock	15
		wood       Effect_PistolDirt		imp_20mm_wood	5
		metal      Effect_PistolMetal		imp_20mm_metal	15
		glass      Effect_PistolGlass		imp_glass			5
		cloth      Effect_PistolDirt		IMP_20MM_CLOTH 3
		foliage    Effect_PistolGrass		imp_20mm_foliage 3
		hmetal     Effect_PistolMetal		imp_20mm_armor	15
		flesh      Effect_PistolBody		imp_20mm_flesh	3
		player		none					imp_20mm_flesh	10
		zip			none					wsh_shell_by	10
	end
end

ammo ROCKET
	bullet_mass 3
	frndlyTrcrID 4502   
	max_age 11     
	arm_age 0      
	velocity 50
	error 0
	drag  1
    ai_launch		GS_AT4 

	scorch_id 2
	scar_type 2

	kztype rounds_kz_C4  
	kz_minradius 3.0
	kz_maxradius 7.0
	kz_damage    700
	impact_damage 128

	kz_physics	1

	light_move     6.0   128 120 80
	light_impact   10.0  255 192 96  0.2

	flag LAWR
	flag NoGravity
	flag forcetracer

    impact_AI_damage 43	
    kz_AI_damage    233 

	effects_table
		move       Effect_AT4Trust		none				0
		obj        Effect_PRGDirt		explo_ammo_med		200
		dirt       Effect_PRGDirt		explo_dirt			200
		grass      Effect_PRGDirt		explo_ammo_med		200
		snow       Effect_PRGDirt		explo_dirt			200
		cement     Effect_PRGDirt		explo_ammo_med		200
		packeddirt Effect_PRGDirt		explo_dirt			200
		water      Effect_WaterExp		explo_water_sm		200
		railroad   Effect_PRGDirt		explo_ammo_med		200
		mud        Effect_PRGDirt		explo_ammo_med		200
		ice        Effect_PRGDirt		explo_dirt			200
		quicksand  Effect_PRGDirt		explo_dirt			200
		sand	   Effect_PRGDirt		explo_dirt			200
		stone      Effect_PRGDirt 		explo_ammo_med		200
		wood       Effect_PRGDirt		explo_ammo_med		200
		metal      Effect_PRGDirt		explo_ammo_med		200
		glass      Effect_PRGDirt		explo_ammo_med		200
		cloth      Effect_PRGDirt		explo_ammo_med		200
		foliage    Effect_PRGDirt		explo_foliage		200
		hmetal     Effect_PRGDirt		explo_ammo_med		200
		flesh      Effect_PRGDirt		explo_ammo_med		200
		player	   Effect_PRGDirt		explo_ammo_med		200
		zip			none				WSH_AT4_BY			10
	end
end

ammo ROCKETAT4
	bullet_mass 3
	frndlyTrcrID 4502   
	max_age 5     
	arm_age 0      
	velocity 290
	error 0
	drag  1
    ai_launch		GS_AT4 
	recoil		30

	Mf_Light 100

	scorch_id 2
	scar_type 2

	kztype rounds_kz_C4  
	kz_minradius 3.0
	kz_maxradius 7.0
	kz_damage    800
	impact_damage 1

	kz_physics	1

	light_move     6.0   128 120 80
	light_impact   10.0  255 192 96  0.2

	flag LAWR
	flag NoGravity
	flag	IgnorFoilage
	flag forcetracer
	flag	priority	

    impact_AI_damage 43	
    kz_AI_damage    266 

	effects_table
		move       Effect_AT4Trust		none				0
		obj        Effect_PRGDirt		explo_ammo_med		200
		dirt       Effect_PRGDirt		explo_dirt			200
		grass      Effect_PRGDirt		explo_ammo_med		200
		snow       Effect_PRGDirt		explo_dirt			200
		cement     Effect_PRGDirt		explo_ammo_med		200
		packeddirt Effect_PRGDirt		explo_dirt			200
		water      Effect_WaterExp		explo_water_sm		200
		railroad   Effect_PRGDirt		explo_ammo_med		200
		mud        Effect_PRGDirt		explo_ammo_med		200
		ice        Effect_PRGDirt		explo_dirt			200
		quicksand  Effect_PRGDirt		explo_dirt			200
		sand	   Effect_PRGDirt		explo_dirt			200
		stone      Effect_PRGDirt 		explo_ammo_med		200
		wood       Effect_PRGDirt		explo_ammo_med		200
		metal      Effect_PRGDirt		explo_ammo_med		200
		glass      Effect_PRGDirt		explo_ammo_med		200
		cloth      Effect_PRGDirt		explo_ammo_med		200
		foliage    Effect_PRGDirt		explo_foliage		200
		hmetal     Effect_PRGDirt		explo_ammo_med		200
		flesh      Effect_PRGDirt		explo_ammo_med		200
		player	   Effect_PRGDirt		explo_ammo_med		200
		zip			none				WSH_AT4_BY			10
	end
end


ammo STINGER
	bullet_mass 3
	frndlyTrcrID 4504   
	max_age 10     
	arm_age 0      
	velocity 250 
	error 0
	drag  1
    ai_launch		GS_STINGER 

	scorch_id 2
	scar_type 2

	turnrate_maxpit  120
	turnrate_maxyaw  120
	heat_det_range 3000.0
	boresight_maxang 5   

	kztype rounds_kz_C4
	kz_minradius 1.0
	kz_maxradius 13.0
	kz_damage 32
	impact_damage 128

	kz_physics	1

	light_move     6.0  128 120 80
	light_impact   8.0  255 192 96  0.2

	flag LAWR
	flag NoGravity
	flag forcetracer

    impact_AI_damage 43	
    kz_AI_damage    11 

	effects_table
		move		none     none				0
		obj        Effect_AirExp		explo_ammo_med		200
		dirt       Effect_DirtExp		explo_dirt			200
		grass      Effect_GrassExp		explo_ammo_med		200
		snow       Effect_SnowExp		explo_dirt			200
		cement     Effect_StoneExp		explo_ammo_med		200
		packeddirt Effect_DirtExp		explo_dirt			200
		water      Effect_WaterExp		explo_water_sm		200
		railroad   effect_airexp		explo_ammo_med		200
		mud        Effect_DirtExp		explo_ammo_med		200
		ice        Effect_SnowExp		explo_dirt			200
		quicksand	Effect_DirtExp		explo_dirt			200
		sand		Effect_DirtExp		explo_dirt			200
		stone      Effect_StoneExp		explo_ammo_med		200
		wood       Effect_SmlAirExp		explo_ammo_med		200
		metal      effect_airexp		explo_ammo_med		200
		glass      effect_airexp		explo_ammo_med		200
		cloth      effect_airexp		explo_ammo_med		200
		foliage    Effect_AirExp		explo_foliage		200
		hmetal     effect_airexp		explo_ammo_med		200
		flesh      effect_airexp		explo_ammo_med		200
		player		none				explo_ammo_med		200
		zip			none				by_missile1			10
	end
end

ammo ARTILLERY
	bullet_mass 5
	max_age 16     
	arm_age 5
	frndlyTrcrID 4407

	flag useownmove

end


ammo ARTYRND
	bullet_mass 1
	max_age 20     
	velocity 150	

	error 0
	drag  1
	scorch_id 1
	scar_type 1
	frndlyTrcrID 4405
	foeTrcrID	 4406
    ai_launch		ARTY_INCOMING 

	kztype rounds_kz_Bullets
	kz_damage 256
	kz_minradius 5.0
	kz_maxradius 30.0
	impact_damage 1024

    impact_AI_damage 340	
    kz_AI_damage    85 

	effects_table
		move       Effect_Flare                none              0
		obj        Effect_AirExp		explo_artillery	15
		dirt       Effect_DirtExp		explo_artillery	15
		grass      Effect_GrassExp		explo_artillery	15
		snow       Effect_SnowExp		explo_artillery	1
		cement     Effect_StoneExp		explo_artillery	15
		packeddirt Effect_DirtExp		explo_artillery	15
		water      Effect_WaterExp		explo_water_lg	5
		railroad   Effect_AirExp		explo_artillery	15
		mud        Effect_DirtExp		explo_artillery	15
		ice        Effect_SnowExp		explo_artillery	15
		sand       Effect_DirtExp		explo_artillery	15
		quicksand  Effect_DirtExp		explo_artillery	15
		stone      Effect_StoneExp		explo_artillery	15
		wood       effect_WoodExp		explo_artillery	5
		metal      Effect_AirExp		explo_artillery	15
		glass      none                 explo_artillery	5
		cloth      Effect_AirExp	    explo_artillery	3
		foliage    Effect_FoliageExp	explo_artillery	3
		hmetal     Effect_AirExp	    explo_artillery	15
		flesh      Effect_AirExp	    explo_artillery	3
		player	   none					explo_artillery	10
		zip		   none					wsh_shell_by	10
	end
end

ammo AI_STINGER
	bullet_mass 3
	frndlyTrcrID 4504   
	max_age 10     
	arm_age 0      
	velocity 100 
	error 0
	drag  1
    ai_launch		GS_STINGER 

	Mf_Light 100

	turnrate_maxpit  120
	turnrate_maxyaw  120
	boresight_maxang 45   
    heat_det_range 2000

	scorch_id 2
	scar_type 2

	kztype rounds_kz_C4
	kz_minradius 1.0
	kz_maxradius 13.0
	
	kz_damage		32
    kz_AI_damage    32 
	impact_damage	128
    impact_AI_damage 128
	kz_physics	1



	light_move     6.0  128 120 80
	light_impact   8.0  255 192 96  0.25

	flag LAWR
	flag NoGravity
	flag forcetracer



	effects_table
		move	   effect_fireball      none				0
		obj        Effect_SmlAirExp		explo_ammo_med		200
		dirt       Effect_SmlDirtExp	explo_dirt			200
		grass      Effect_SmlGrassExp	explo_ammo_med		200
		snow       Effect_SmlSnowExp	explo_dirt			200
		cement     Effect_StoneAirExp	explo_ammo_med		200
		packeddirt Effect_SmlDirtExp	explo_dirt			200
		water      effect_waterexp		explo_water_sm		200
		railroad   Effect_SmlAirExp		explo_ammo_med		200
		mud        Effect_SmlDirtExp	explo_ammo_med		200
		ice        Effect_SmlSnowExp	explo_dirt			200
		quicksand	Effect_SmlDirtExp	explo_dirt			200
		sand		Effect_SmlDirtExp	explo_dirt			200
		stone      Effect_StoneAirExp	explo_ammo_med		200
		wood       effect_WoodExp		explo_ammo_med		200
		metal      Effect_SmlAirExp		explo_ammo_med		200
		glass      Effect_SmlAirExp		explo_ammo_med		200
		cloth      Effect_SmlAirExp		explo_ammo_med		200
		foliage    Effect_FoliageExp	explo_foliage		200
		hmetal     Effect_SmlAirExp		explo_ammo_med		200
		flesh      Effect_SmlAirExp		explo_ammo_med		200
		player		Effect_SmlAirExp	explo_ammo_med		200
		zip			none				by_missile1			10
	end
end

ammo 30MM
	bullet_mass 1
	max_age 3     
	velocity 300	
	error 0
	drag  1
	scorch_id 1
	scar_type 1
	frndlyTrcrID 4405
	foeTrcrID	 4406
    ai_launch		GS_30MM 

	Mf_Light 100

	kztype rounds_kz_Bullets
	kz_damage 24
	kz_minradius 1.0
	kz_maxradius 4.0
	impact_damage 24
    flag muzzle1  

    impact_AI_damage 8	
    kz_AI_damage    8 

	effects_table
		move       none					none              0
		obj        Effect_PistolMetal	imp_30mm_dirt	15
		dirt       Effect_PistolDirt	imp_30mm_dirt	15
		grass      Effect_PistolGrass	imp_20mm_dirt	15
		snow       Effect_PistolSnow	imp_30mm_dirt	1
		cement     Effect_PistolStone	imp_30mm_dirt	15
		packeddirt Effect_PistolDirt	imp_30mm_dirt	15
		water      Effect_PistolWater	imp_20mm_water	5
		railroad   Effect_PistolMetal	imp_30mm_metal	15
		mud        Effect_PistolDirt	imp_bullet_mud   15
		ice        Effect_PistolSnow	IMP_BULLET_SAND	15
		sand       Effect_PistolSand    IMP_BULLET_SAND	15
		quicksand  Effect_PistolSand    IMP_BULLET_SAND	15
		stone      Effect_PistolStone   imp_30mm_rock	15
		wood       Effect_PistolWood    imp_20mm_wood	5
		metal      Effect_PistolMetal   imp_30mm_metal	15
		glass      Effect_PistolGlass   imp_glass			5
		cloth      Effect_PistolDirt	IMP_BULLET_SAND 3
		foliage    Effect_PistolFoliage	imp_20mm_foliage 3
		hmetal     Effect_PistolMetal	imp_30mm_armor	15
		flesh      Effect_PistolBody	imp_20mm_flesh	3
		player	   Effect_PistolBody	imp_20mm_flesh	10
		zip			none				wsh_shell_by	10
	end
end


ammo MAIN_CANNON
	bullet_mass 1
	max_age 3     
	velocity 300
	error 0
	drag  1
	scorch_id 2
	scar_type 2
	frndlyTrcrID 4405
	foeTrcrID	 4406
    ai_launch		GS_HOWITZER 

	Mf_Light 100

	kztype rounds_kz_Bullets
	kz_damage 100
	kz_minradius 2.0
	kz_maxradius 10.0
	impact_damage 220
    flag muzzle2  

    impact_AI_damage 33	
    kz_AI_damage    73 

	effects_table
		move       none                none					0
		obj        Effect_SmlAirExp		explo_ammo_med		 15
		dirt       Effect_SmlDirtExp    explo_dirt			15
		grass      Effect_SmlGrassExp   explo_ammo_med		15
		snow       Effect_SmlSnowExp    explo_dirt			1
		cement     Effect_StoneAirExp   explo_ammo_med		15
		packeddirt Effect_SmlDirtExp    explo_dirt			15
		water      effect_waterexp		explo_water_sm		5
		railroad   Effect_SmlAirExp		explo_ammo_med		15
		mud        Effect_SmlDirtExp    explo_ammo_med		15
		ice        Effect_SmlSnowExp    explo_dirt			15
		sand       Effect_SmlDirtExp    explo_dirt			15
		quicksand  Effect_SmlDirtExp    explo_dirt			15
		stone      Effect_StoneAirExp   explo_ammo_med		15
		wood       effect_WoodExp		explo_ammo_med		5
		metal      Effect_SmlAirExp		explo_ammo_med		15
		glass      none                 explo_ammo_med		5
		cloth      Effect_SmlAirExp		explo_ammo_med		3
		foliage    Effect_PistolFoliage	explo_foliage		3
		hmetal     Effect_SmlAirExp		explo_ammo_med		15
		flesh      Effect_SmlAirExp		explo_ammo_med		3
		player		none				explo_ammo_med		10
		zip			none				WSH_BULLET_BY		20
	end
end

ammo SIDEWINDER
	bullet_mass 3
	frndlyTrcrID 4504   
	max_age 10     
	arm_age 0      
	velocity 250 
	error 0
	drag  1
    ai_launch		GS_SIDEWINDER 

	Mf_Light 100
	scorch_id 2
	scar_type 2

	turnrate_maxpit  60
	turnrate_maxyaw  60
	boresight_maxang 15
	heat_det_range 3000.0


	kztype rounds_kz_C4
	kz_minradius 1.0
	kz_maxradius 10.0
	kz_damage 64
	impact_damage 192

	kz_physics	1

	light_move     6.0  128 120 80
	light_impact   8.0  255 192 96  0.25

	flag LAWR
	flag NoGravity
	flag forcetracer

    impact_AI_damage 64	
    kz_AI_damage    22 

	effects_table
		move		none     none				0
		obj        Effect_SmlAirExp		explo_ammo_lg		200
		dirt       Effect_SmlDirtExp	explo_dirt			200
		grass      Effect_SmlGrassExp	explo_ammo_lg		200
		snow       Effect_SmlSnowExp	explo_dirt			200
		cement     Effect_StoneAirExp	explo_ammo_lg		200
		packeddirt Effect_SmlDirtExp	explo_dirt			200
		water      effect_waterexp		explo_water_lg		200
		railroad   Effect_SmlAirExp		explo_ammo_lg		200
		mud        Effect_SmlDirtExp	explo_ammo_lg		200
		ice        Effect_SmlSnowExp	explo_dirt			200
		quicksand	Effect_SmlDirtExp	explo_dirt			200
		sand		Effect_SmlDirtExp	explo_dirt			200
		stone      Effect_StoneAirExp	explo_ammo_lg		200
		wood       effect_WoodExp		explo_ammo_lg		200
		metal      Effect_SmlAirExp		explo_ammo_lg		200
		glass      Effect_SmlAirExp		explo_ammo_lg		200
		cloth      Effect_SmlAirExp		explo_ammo_lg		200
		foliage    Effect_FoliageExp	explo_foliage		200
		hmetal     Effect_SmlAirExp		explo_ammo_lg		200
		flesh      Effect_SmlAirExp		explo_ammo_lg		200
		player		none				explo_ammo_lg		200
		zip			none				by_missile1			50
	end
end

ammo ROTOR_BLADE
	bullet_mass 1
	max_age 0.2     
	velocity 100
	error 0
	drag  1
	scorch_id 1
	scar_type 1

	impact_damage 8

    impact_AI_damage 3	
    kz_AI_damage    0 

	effects_table
		move       none						none              0
		obj        none						none	15
		dirt       Effect_PistolDirt		none	15
		grass      Effect_PistolGrass		none	15
		snow       Effect_PistolSnow		none	1
		cement     Effect_PistolDirt		IMP_ROTOR_THING	15
		packeddirt Effect_PistolDirt		none	15
		water      Effect_SmlSplash			imp_rotor_water	5
		railroad   Effect_PistolMetal		IMP_ROTOR_THING	15
		mud        Effect_PistolDirt		none	15
		ice        Effect_PistolSnow		none	15
		sand       Effect_PistolSand		none	15
		quicksand  Effect_PistolSand		none	15
		stone      Effect_PistolStone		none	15
		wood       Effect_PistolWood			none	5
		metal      Effect_PistolMetal		IMP_ROTOR_THING	15
		glass      Effect_PistolGlass		none	5
		cloth      Effect_PistolObj		none	3
		foliage    Effect_PistolFoliage		IMP_ROTOR_TREE	3
		hmetal     Effect_PistolMetal		IMP_ROTOR_THING	15
		flesh      Effect_PistolBody		none 3
		player		none					none	10
		zip			none					none		10
	end
end

ammo AI_ROCKET_POD
	bullet_mass 3
	frndlyTrcrID 4502   
	max_age 10     
	arm_age 0      
	velocity 200
	error 0
	drag  1
    ai_launch		GS_AIROCKET 

	Mf_Light 100

	scorch_id 2
	scar_type 2

	kztype rounds_kz_C4  
	kz_minradius 2.0
	kz_maxradius 10.0
	kz_damage		32
    kz_AI_damage    32
	impact_damage	128
    impact_AI_damage 128	

	kz_physics	1

	light_move     6.0   128 120 80
	light_impact   10.0  255 192 96  0.2

	flag LAWR
	flag NoGravity
	flag forcetracer
 

	effects_table
		move       none      none					0
		obj        Effect_SmlAirExp		explo_ammo_med		200
		dirt       Effect_SmlDirtExp	explo_dirt			200
		grass      Effect_SmlGrassExp	explo_ammo_med		200
		snow       Effect_SmlSnowExp	explo_dirt			200
		cement     Effect_StoneAirExp	explo_ammo_med		200
		packeddirt Effect_SmlDirtExp	explo_dirt			200
		water      Effect_SmlWatExp		explo_water_sm		200
		railroad   Effect_SmlAirExp		explo_ammo_med		200
		mud        Effect_SmlDirtExp	explo_ammo_med		200
		ice        Effect_SmlSnowExp	explo_dirt			200
		quicksand	Effect_SmlDirtExp	explo_dirt			200
		sand		Effect_SmlDirtExp	explo_dirt			200
		stone      Effect_StoneAirExp	explo_ammo_med		200
		wood       Effect_WoodExp		explo_ammo_med		200
		metal      Effect_SmlAirExp		explo_ammo_med		200
		glass      Effect_SmlAirExp		explo_ammo_med		200
		cloth      Effect_SmlAirExp		explo_ammo_med		200
		foliage    Effect_FoliageExp	explo_foliage		200
		hmetal     Effect_SmlAirExp		explo_ammo_med		200
		flesh      Effect_SmlAirExp		explo_ammo_med		200
		player		none				explo_ammo_med		200
		zip			none				by_missile1			50
	end
end

ammo AI_LAW
	bullet_mass 3
	frndlyTrcrID 4502   
	max_age 10     
	arm_age 0      
	velocity 20 
	error 0
	drag  1
    ai_launch		GS_LAW 

	Mf_Light 100

	scorch_id 2
	scar_type 2

	kztype rounds_kz_C4
	kz_minradius 1.0
	kz_maxradius 13.0
	kz_damage		32	
    kz_AI_damage	32
	impact_damage	128
    impact_AI_damage 128

	kz_physics	1


	light_move     6.0  128 120 80
	light_impact   8.0  255 192 96  0.25

	flag LAWR
	flag NoGravity
	flag forcetracer
 

	effects_table
		move		effect_acidspit      none				0
		obj        Effect_SmlAirExp		explo_ammo_med		200
		dirt       Effect_SmlDirtExp	explo_dirt			200
		grass      Effect_SmlGrassExp	explo_ammo_med		200
		snow       Effect_SmlSnowExp	explo_dirt			200
		cement     Effect_StoneAirExp	explo_ammo_med		200
		packeddirt Effect_SmlDirtExp	explo_dirt			200
		water      effect_waterexp		explo_water_sm		200
		railroad   Effect_SmlAirExp		explo_ammo_med		200
		mud        Effect_SmlDirtExp	explo_ammo_med		200
		ice        Effect_SmlSnowExp	explo_dirt			200
		quicksand	Effect_SmlDirtExp	explo_dirt			200
		sand		Effect_SmlDirtExp	explo_dirt			200
		stone      Effect_StoneAirExp	explo_ammo_med		200
		wood       Effect_WoodExp		explo_ammo_med		200
		metal      Effect_SmlAirExp		explo_ammo_med		200
		glass      Effect_SmlAirExp		explo_ammo_med		200
		cloth      Effect_SmlAirExp		explo_ammo_med		200
		foliage    Effect_FoliageExp	explo_foliage		200
		hmetal     Effect_SmlAirExp		explo_ammo_med		200
		flesh      Effect_SmlAirExp		explo_ammo_med		200
		player	   Effect_SmlAirExp		explo_ammo_med		200
		zip			none				by_missile1			50
	end
end

ammo AI_20MM
	bullet_mass 1
	max_age 3.5     
	velocity 300	
	error 0
	drag  1
	scorch_id 1
	scar_type 1
	frndlyTrcrID 4405
	foeTrcrID	 4406
	impact_damage		16
    impact_AI_damage	16
    ai_launch		GS_20MM 

	Mf_Light 100

	kztype rounds_kz_Bullets
	kz_damage		8	
    kz_AI_damage    8
	kz_minradius 2.0
	kz_maxradius 3.0
    flag muzzle1  
 

	effects_table
		move		none					none				0
		obj			Effect_PistolMetal		imp_20mm_dirt		15
		dirt		Effect_PistolDirt		imp_20mm_dirt		15
		grass		Effect_PistolGrass		imp_bullet_grass	15
		snow		Effect_PistolSnow		imp_20mm_dirt		1
		cement		Effect_PistolStone		imp_20mm_dirt		15
		packeddirt	Effect_PistolDirt		imp_20mm_dirt		15
		water		Effect_PistolWater		imp_20mm_water		5
		railroad	Effect_PistolMetal		imp_20mm_metal		15
		mud			Effect_PistolDirt		imp_bullet_mud		15
		ice			Effect_PistolSnow		imp_bullet_mud		15
		sand		Effect_PistolSand		IMP_BULLET_SAND		15
		quicksand	Effect_PistolSand		IMP_BULLET_SAND		15
		stone		Effect_PistolStone		imp_20mm_rock		15
		wood		Effect_PistolWood		imp_20mm_wood		5
		metal		Effect_PistolMetal		imp_20mm_metal		15
		glass		Effect_PistolGlass		imp_glass			5
		cloth		Effect_PistolDirt		IMP_BULLET_SAND		3
		foliage		Effect_PistolFoliage	imp_20mm_foliage	3
		hmetal		Effect_PistolMetal		imp_20mm_armor		15
		flesh		Effect_PistolBody		imp_20mm_flesh		3
		player		Effect_PistolBody		imp_20mm_flesh		10
		zip			none					wsh_shell_by		10
	end
end

ammo AI_M16		
	bullet_mass 1
	max_age 2     
	velocity 900	
	error 0
	drag  1
	scorch_id 0
	scar_type 0
	frndlyTrcrID 4405
	foeTrcrID	 4406
    ai_launch		GS_M16AI 
	ai_Launcheffect Effect_M4MuzFlashFp
	recoil	24

	Mf_Light 100

	impact_damage 40

	kztype rounds_kz_C4  
	kz_damage 0
	kz_minradius 2.5
	kz_maxradius 2.5

    flag muzzle1  

    impact_AI_damage 13	
    kz_AI_damage    0 

	effects_table
		move		none					none				0
		obj			Effect_PistolMetal		IMP_BULLET_DIRT		15
		dirt		Effect_PistolDirt		IMP_BULLET_DIRT		15
		grass		Effect_PistolGrass		imp_bullet_grass	15
		snow		Effect_PistolSnow		IMP_BULLET_DIRT		1
		cement		Effect_PistolStone		IMP_BULLET_ROCK		15
		packeddirt	Effect_PistolDirt		imp_20mm_dirt		15
		water		Effect_PistolWater		IMP_BULLET_WATER	5
		railroad	Effect_PistolMetal		IMP_BULLET_METAL	15
		mud			Effect_PistolDirt		imp_bullet_mud		15
		ice			Effect_PistolSnow		imp_bullet_mud		15
		sand		Effect_PistolSand		IMP_BULLET_SAND		15
		quicksand	Effect_PistolSand		IMP_BULLET_SAND		15
		stone		Effect_PistolStone		IMP_BULLET_ROCK		15
		wood		Effect_PistolWood		IMP_BULLET_WOOD		5
		metal		Effect_PistolMetal		IMP_BULLET_METAL	15
		glass		Effect_PistolGlass		imp_glass			5
		cloth		Effect_PistolDirt		IMP_BULLET_CLOTH	3
		foliage		Effect_PistolFoliage	IMP_BULLET_FOLIAGE	3
		hmetal		Effect_PistolMetal		IMP_BULLET_ARMOR	15
		flesh		Effect_PistolBody		IMP_BULLET_FLESH	3
		player		Effect_PistolBody		imp_bullet_flesh	10
		zip			none					WSH_BULLET_BY2		10
	end
end

ammo AI_CAR15		
	bullet_mass 1
	max_age 2     
	velocity 900	
	error 0
	drag  1
	scorch_id 0
	scar_type 0
	frndlyTrcrID 4405
	foeTrcrID	 4406
    ai_launch		GS_CAR15AI 
	ai_Launcheffect Effect_M4MuzFlashFp
	recoil	24

	Mf_Light 100

	impact_damage 40

	kztype rounds_kz_C4  
	kz_damage 0
	kz_minradius 2.5
	kz_maxradius 2.5

    flag muzzle1  

    impact_AI_damage 13	
    kz_AI_damage    0 

	effects_table
		move		none					none				0
		obj			Effect_PistolMetal		IMP_BULLET_DIRT		15
		dirt		Effect_PistolDirt		IMP_BULLET_DIRT		15
		grass		Effect_PistolGrass		imp_bullet_grass	15
		snow		Effect_PistolSnow		IMP_BULLET_DIRT		1
		cement		Effect_PistolStone		IMP_BULLET_ROCK		15
		packeddirt	Effect_PistolDirt		imp_20mm_dirt		15
		water		Effect_PistolWater		IMP_BULLET_WATER	5
		railroad	Effect_PistolMetal		IMP_BULLET_METAL	15
		mud			Effect_PistolDirt		imp_bullet_mud		15
		ice			Effect_PistolSnow		imp_bullet_mud		15
		sand		Effect_PistolSand		IMP_BULLET_SAND		15
		quicksand	Effect_PistolSand		IMP_BULLET_SAND		15
		stone		Effect_PistolStone		IMP_BULLET_ROCK		15
		wood		Effect_PistolWood		IMP_BULLET_WOOD		5
		metal		Effect_PistolMetal		IMP_BULLET_METAL	15
		glass		Effect_PistolGlass		imp_glass			5
		cloth		Effect_PistolDirt		IMP_BULLET_SAND		3
		foliage		Effect_PistolFoliage	IMP_BULLET_FOLIAGE	3
		hmetal		Effect_PistolMetal		IMP_BULLET_ARMOR	15
		flesh		Effect_PistolBody		IMP_BULLET_FLESH	3
		player		Effect_PistolBody		imp_bullet_flesh	10
		zip			none					WSH_BULLET_BY2		10
	end
end

ammo AI_AK47a		
	bullet_mass 1
	max_age 2     
	velocity 862	
	error 0
	drag  1
	scorch_id 0
	scar_type 0
	frndlyTrcrID 4405
	foeTrcrID	 4406
	tracerRate	 3				
    ai_launch		GS_AK47_2 
	ai_Launcheffect Effect_EnmyMuzz
	recoil	24

	Mf_Light 100

	impact_damage 15
    impact_AI_damage 15

	kztype rounds_kz_C4  
	kz_damage		0
    kz_AI_damage    0
	kz_minradius 2.5
	kz_maxradius 2.5

    flag muzzle1  
 

	effects_table
		move		none					none				0
		obj			Effect_PistolMetal		imp_bullet_dirt		15
		dirt		Effect_PistolDirt		imp_bullet_dirt		15
		grass		Effect_PistolGrass		imp_bullet_grass	15
		snow		Effect_PistolSnow		imp_bullet_dirt		1
		cement		Effect_PistolStone		imp_bullet_dirt		15
		packeddirt	Effect_PistolDirt		imp_bullet_dirt		15
		water		Effect_PistolWater		imp_bullet_water	5
		railroad	Effect_PistolMetal		imp_bullet_metal	15
		mud			Effect_PistolDirt		imp_bullet_mud		15
		ice			Effect_PistolSnow		imp_bullet_mud		15
		sand		Effect_PistolSand		imp_bullet_sand		15
		quicksand	Effect_PistolSand		imp_bullet_sand		15
		stone		Effect_PistolStone		imp_bullet_rock		15
		wood		Effect_PistolWood		imp_bullet_wood		5
		metal		Effect_PistolMetal		imp_bullet_metal	15
		glass		Effect_PistolGlass		imp_glass			5
		cloth		Effect_PistolDirt		IMP_BULLET_SAND		3
		foliage		Effect_PistolFoliage	IMP_BULLET_FOLIAGE	3
		hmetal		Effect_PistolMetal		imp_bullet_armor	15
		flesh		Effect_PistolBody		imp_bullet_flesh	3
		player		Effect_PistolBody		IMP_BULLET_PLAYER	10
		zip			none					wsh_bullet_by2		3
	end
end


ammo AI_AK47b		
	bullet_mass 1
	max_age 2     
	velocity 862	
	error 0
	drag  1
	scorch_id 0
	scar_type 0
	frndlyTrcrID 4405
	foeTrcrID	 4406
	tracerRate	 3				
    ai_launch		GS_AK47 
	ai_Launcheffect Effect_EnmyMuzz
	recoil	24

	Mf_Light 100

	impact_damage 15
    impact_AI_damage 15

	kztype rounds_kz_C4  
	kz_damage		0
    kz_AI_damage    0
	kz_minradius 2.5
	kz_maxradius 2.5

    flag muzzle1  
 

	effects_table
		move		none					none				0
		obj			Effect_PistolMetal		imp_bullet_dirt		15
		dirt		Effect_PistolDirt		imp_bullet_dirt		15
		grass		Effect_PistolGrass		imp_bullet_grass	15
		snow		Effect_PistolSnow		imp_bullet_dirt		1
		cement		Effect_PistolStone		imp_bullet_dirt		15
		packeddirt	Effect_PistolDirt		imp_bullet_dirt		15
		water		Effect_PistolWater		imp_bullet_water	5
		railroad	Effect_PistolMetal		imp_bullet_metal	15
		mud			Effect_PistolDirt		imp_bullet_mud		15
		ice			Effect_PistolSnow		imp_bullet_mud		15
		sand		Effect_PistolSand		imp_bullet_sand		15
		quicksand	Effect_PistolSand		imp_bullet_sand		15
		stone		Effect_PistolStone		imp_bullet_rock		15
		wood		Effect_PistolWood		imp_bullet_wood		5
		metal		Effect_PistolMetal		imp_bullet_metal	15
		glass		Effect_PistolGlass		imp_glass			5
		cloth		Effect_PistolDirt		IMP_BULLET_SAND		3
		foliage		Effect_PistolFoliage	IMP_BULLET_FOLIAGE	3
		hmetal		Effect_PistolMetal		imp_bullet_armor	15
		flesh		Effect_PistolBody		imp_bullet_flesh	3
		player		Effect_PistolBody		IMP_BULLET_PLAYER	10
		zip			none					wsh_bullet_by2		3
	end
end



ammo AI_30MM
	bullet_mass 1
	max_age 3.5     
	velocity 300	
	error 0
	drag  1
	scorch_id 1
	scar_type 1
	frndlyTrcrID 4405
	foeTrcrID	 4406
    ai_launch		GS_30MM 

	Mf_Light 100

	kztype rounds_kz_Bullets
	kz_damage		24
    kz_AI_damage    24
	kz_minradius 1.0
	kz_maxradius 4.0
	impact_damage	24
    impact_AI_damage 24
    flag muzzle1  
	


	effects_table
		move		none				none				0
		obj			Effect_PistolMetal	imp_30mm_dirt		15
		dirt		Effect_PistolDirt	imp_30mm_dirt		15
		grass		Effect_PistolGrass	imp_20mm_dirt		15
		snow		Effect_PistolSnow	imp_30mm_dirt		1
		cement		Effect_PistolStone	imp_30mm_dirt		15
		packeddirt	Effect_PistolDirt	imp_30mm_dirt		15
		water		Effect_PistolWater	imp_20mm_water		5
		railroad	Effect_PistolMetal	imp_30mm_metal		15
		mud			Effect_PistolDirt	imp_bullet_mud		15
		ice			Effect_PistolSnow	IMP_BULLET_SAND		15
		sand		Effect_PistolSand   IMP_BULLET_SAND		15
		quicksand	Effect_PistolSand   IMP_BULLET_SAND		15
		stone		Effect_PistolStone  imp_30mm_rock		15
		wood		Effect_PistolWood   imp_20mm_wood		5
		metal		Effect_PistolMetal  imp_30mm_metal		15
		glass		Effect_PistolGlass  imp_glass			5
		cloth		Effect_PistolDirt	IMP_BULLET_SAND	3
		foliage		Effect_PistolFoliage	imp_20mm_foliage	3
		hmetal		Effect_PistolMetal	imp_30mm_armor		15
		flesh		Effect_PistolBody	imp_20mm_flesh		3
		player		Effect_PistolBody	imp_20mm_flesh		10
		zip			none				wsh_shell_by		10
	end
end

ammo AI_50CAL
	bullet_mass 1
	max_age 3     
	velocity 300
	error 0
	drag  1
	scorch_id 0
	scar_type 1
	frndlyTrcrID 4405
	foeTrcrID	 4406
    ai_launch		GS_AI50CAL 
    flag muzzle1	  

	Mf_Light 100

	impact_damage 8
    impact_AI_damage 8	

	kztype rounds_kz_C4  
	kz_damage 0
    kz_AI_damage    0
	kz_minradius 2.5
	kz_maxradius 2.5

 

	effects_table
		move       none					none				0
		obj			Effect_PistolMetal	imp_bullet_dirt		15
		dirt		Effect_PistolDirt	imp_bullet_dirt		15
		grass		Effect_PistolGrass	imp_bullet_grass	15
		snow		Effect_PistolSnow	imp_bullet_dirt		1
		cement		Effect_PistolStone	imp_bullet_dirt		15
		packeddirt	Effect_PistolDirt	imp_bullet_dirt		15
		water		Effect_PistolWater	imp_bullet_water	5
		railroad	Effect_PistolMetal	imp_bullet_metal	15
		mud			Effect_PistolDirt	imp_bullet_mud		15
		ice			Effect_PistolSnow	imp_bullet_mud		15
		sand		Effect_PistolSand   imp_bullet_sand		15
		quicksand	Effect_PistolSand   imp_bullet_sand		15
		stone		Effect_PistolStone  imp_bullet_rock		15
		wood		Effect_PistolWood   imp_bullet_wood		5
		metal		Effect_PistolMetal  imp_bullet_metal	15
		glass		Effect_PistolGlass  imp_glass			5
		cloth		Effect_PistolDirt	IMP_BULLET_SAND		3
		foliage		Effect_PistolFoliage	IMP_20MM_FOLIAGE		3
		hmetal		Effect_PistolMetal	imp_bullet_armor	15
		flesh		Effect_PistolBody	imp_bullet_flesh	3
		player		Effect_PistolBody	imp_bullet_flesh	10
		zip			none				wsh_shell_by		20
	end
end

ammo AI_MAIN_CANNON
	bullet_mass 1
	max_age 3     
	velocity 600
	error 0
	drag  1
	scorch_id 2
	scar_type 2
	frndlyTrcrID 4405
	foeTrcrID	 4406
    ai_launch		GS_HOWITZER 
    flag muzzle2  
	kztype rounds_kz_Bullets
	kz_damage		100
    kz_AI_damage    100

	Mf_Light 100

	kz_minradius 2.0
	kz_maxradius 10.0
	impact_damage	 220
    impact_AI_damage 220


	effects_table
		move       none		none					0
		obj        Effect_SmlAirExp		explo_ammo_med		200
		dirt       Effect_SmlDirtExp	explo_dirt			200
		grass      Effect_SmlGrassExp	explo_ammo_med		200
		snow       Effect_SmlSnowExp	explo_dirt			200
		cement     Effect_StoneAirExp	explo_ammo_med		200
		packeddirt Effect_SmlDirtExp	explo_dirt			200
		water      Effect_SmlWatExp		explo_water_sm		200
		railroad   Effect_SmlAirExp		explo_ammo_med		200
		mud        Effect_SmlDirtExp	explo_ammo_med		200
		ice        Effect_SmlSnowExp	explo_dirt			200
		quicksand	Effect_SmlDirtExp	explo_dirt			200
		sand		Effect_SmlDirtExp	explo_dirt			200
		stone      Effect_StoneAirExp	explo_ammo_med		200
		wood       Effect_WoodExp		explo_ammo_med		200
		metal      Effect_SmlAirExp		explo_ammo_med		200
		glass      Effect_SmlAirExp		explo_ammo_med		200
		cloth      Effect_SmlAirExp		explo_ammo_med		200
		foliage    Effect_FoliageExp	explo_foliage		200
		hmetal     Effect_SmlAirExp		explo_ammo_med		200
		flesh      Effect_SmlAirExp		explo_ammo_med		200
		player		none				explo_ammo_med		200
	end
end

ammo AI_Rock
	bullet_mass	3
	frndlyTrcrID		1905   
	max_age		8     
	arm_age		0      
	velocity	30		
	error		1
	drag		1
	recoil		0


	flag	useownmove
	flag	IgnorFoilage
	flag	forcetracer



    impact_AI_damage 5

	effects_table
		move		none				none				0
		obj			none	IMP_GREN_WOOD		80	
		dirt		none	IMP_ROCK_DIRT		20	
		grass		none	IMP_ROCK_DIRT		20	
		snow		none	IMP_ROCK_DIRT		20	
		cement		none	IMP_ROCK_STONE		20	
		packeddirt	none	IMP_ROCK_DIRT		20	
		water		Effect_SmlSplash	IMP_DEBSML_WATER	20	
		railroad	none	IMP_ROCK_METAL		20	
		mud			none	IMP_ROCK_DIRT		20	
		ice			none	IMP_ROCK_DIRT		20	
		quicksand	none	IMP_ROCK_DIRT		20	
		sand		none	IMP_ROCK_DIRT		20	
		stone		none	IMP_ROCK_STONE		20	
		wood		none	IMP_GREN_WOOD		20	
		metal		none	IMP_ROCK_METAL		20	
		glass		none	IMP_GLASS			20	
		cloth		none	IMP_GREN_CANV		20	
		foliage		none	IMP_GREN_FOLIAGE	20	
		hmetal		none	IMP_ROCK_METAL		20	
		flesh		none	IMP_GREN_FLESH		20	
		player		none	IMP_ROCK_PLAYER		20	
		zip			none				none				10	
	end
end

ammo FLARE
	bullet_mass 1
	max_age 10     
	velocity 0
	error 0
	drag  1
	scorch_id 1
	scar_type 1
	frndlyTrcrID 4408		
    ai_launch		GS_FLARE 
	flag useownmove
	flag forcetracer

	impact_damage 2

    impact_AI_damage 1	
    kz_AI_damage    0 

	effects_table
		move		Effect_Flare		none				0
		obj			none				none				15
		dirt		Effect_PistolDirt	none				15
		grass		Effect_PistolGrass	none				15
		snow		Effect_PistolSnow	none				1
		cement		Effect_PistolDirt	none				15
		packeddirt	Effect_PistolDirt	none				15
		water		Effect_SmlSplash	none				5
		railroad	Effect_PistolMetal	none				15
		mud			Effect_PistolDirt		none				15
		ice			Effect_PistolSnow		none				15
		sand		Effect_PistolSand	none				15
		quicksand	Effect_PistolSand	none				15
		stone		Effect_PistolStone	none				15
		wood		Effect_PistolWood	none				5
		metal		Effect_PistolMetal	none				15
		glass		none				none				5
		cloth		Effect_PistolObj	none				3
		foliage		Effect_PistolFoliage	none				3
		hmetal		Effect_PistolMetal	none				15
		flesh		Effect_PistolBody	none				3
		player		none				none				10
		zip			none				none				10
	end
end

ammo GROUND_FLARE
	bullet_mass 1
	max_age 10     
	velocity 0
	error 0
	drag  1
	scorch_id 1
	scar_type 1
	frndlyTrcrID 4409					
    ai_launch		GS_FLARE	
	flag useownmove
	flag forcetracer

	impact_damage 2

    impact_AI_damage 1	
    kz_AI_damage    0 

	effects_table
		move		none				none				0
		obj			none				none				15
		dirt		Effect_PistolDirt	none				15
		grass		Effect_PistolGrass	none				15
		snow		Effect_PistolSnow	none				1
		cement		Effect_PistolDirt	none				15
		packeddirt	Effect_PistolDirt	none				15
		water		Effect_SmlSplash	none				5
		railroad	Effect_PistolMetal	none				15
		mud			Effect_PistolDirt		none				15
		ice			Effect_PistolSnow		none				15
		sand		Effect_PistolSand	none				15
		quicksand	Effect_PistolSand	none				15
		stone		Effect_PistolStone	none				15
		wood		Effect_PistolWood	none				5
		metal		Effect_PistolMetal	none				15
		glass		none				none				5
		cloth		Effect_PistolObj	none				3
		foliage		Effect_PistolFoliage	none				3
		hmetal		Effect_PistolMetal	none				15
		flesh		Effect_PistolBody	none				3
		player		none				none				10
		zip			none				none				10
	end
end

ammo AI_NAVAL_CANNON
	bullet_mass 1
	max_age 3     
	velocity 600
	error 0
	drag  1
	scorch_id 2
	scar_type 2
	frndlyTrcrID 4405
	foeTrcrID	 4406
    ai_launch		GS_HOWITZER 
    flag muzzle2				
	kztype rounds_kz_Bullets
	kz_damage		100
    kz_AI_damage    100
	kz_minradius 2.0
	kz_maxradius 10.0
	impact_damage	220
    impact_AI_damage 220	

	Mf_Light 100

	effects_table
		move		none				none				0
		obj			Effect_SmlAirExp	explo_ammo_med		200
		dirt		Effect_SmlDirtExp	explo_dirt			200
		grass		Effect_SmlGrassExp	explo_ammo_med		200
		snow		Effect_SmlSnowExp	explo_dirt			200
		cement		Effect_StoneAirExp	explo_ammo_med		200
		packeddirt	Effect_SmlDirtExp	explo_dirt			200
		water		Effect_SmlWatExp	explo_water_sm		200
		railroad	Effect_SmlAirExp	explo_ammo_med		200
		mud			Effect_SmlDirtExp	explo_ammo_med		200
		ice			Effect_SmlSnowExp	explo_dirt			200
		quicksand	Effect_SmlDirtExp	explo_dirt			200
		sand		Effect_SmlDirtExp	explo_dirt			200
		stone		Effect_StoneAirExp	explo_ammo_med		200
		wood		Effect_WoodExp		explo_ammo_med		200
		metal		Effect_SmlAirExp	explo_ammo_med		200
		glass		Effect_SmlAirExp	explo_ammo_med		200
		cloth		Effect_SmlAirExp	explo_ammo_med		200
		foliage		Effect_FoliageExp	explo_foliage		200
		hmetal		Effect_SmlAirExp	explo_ammo_med		200
		flesh		Effect_SmlAirExp	explo_ammo_med		200
		player		none				explo_ammo_med		200
	end
end


ammo AI_MORTAR
	bullet_mass 3
	max_age 7     
	arm_age 0      
	velocity 50		
	error 0
	drag  1
	recoil 0

	scorch_id 2
	scar_type 2
    kz_physics 1		

	ai_launch MORTAR_INCOMING

	kztype rounds_kz_C4  
	kz_minradius 1.0
	kz_maxradius 3.0
	kz_damage		25	
    kz_AI_damage    25 
	impact_damage	 10
    impact_AI_damage 10

	light_impact   8.0  255 192 96  0.25

	flag LAWR
	flag NoGravity


	effects_table
		move		none		      none				0
		obj        Effect_PRGDirt	EXPLO_ARTILLERY		200
		dirt       Effect_PRGDirt	EXPLO_ARTILLERY			200
		grass      Effect_PRGDirt	EXPLO_ARTILLERY		200
		snow       Effect_PRGDirt	EXPLO_ARTILLERY			200
		cement     Effect_PRGDirt	EXPLO_ARTILLERY		200
		packeddirt Effect_PRGDirt	EXPLO_ARTILLERY			200
		water      effect_waterexp	EXPLO_WATER_M		200
		railroad   Effect_PRGDirt	EXPLO_ARTILLERY		200
		mud        Effect_PRGDirt	EXPLO_ARTILLERY		200
		ice        Effect_PRGDirt	EXPLO_ARTILLERY			200
		quicksand	Effect_PRGDirt	EXPLO_ARTILLERY			200
		sand		Effect_PRGDirt	EXPLO_ARTILLERY			200
		stone      Effect_PRGDirt	EXPLO_ARTILLERY		200
		wood       Effect_PRGDirt	EXPLO_ARTILLERY		200
		metal      Effect_PRGDirt	EXPLO_ARTILLERY		200
		glass      Effect_PRGDirt	EXPLO_ARTILLERY		200
		cloth      Effect_PRGDirt	EXPLO_ARTILLERY		200
		foliage    Effect_PRGDirt	EXPLO_ARTILLERY		200
		hmetal     Effect_PRGDirt	EXPLO_ARTILLERY		200
		flesh      Effect_PRGDirt	EXPLO_ARTILLERY		200
		player		Effect_PRGDirt	EXPLO_ARTILLERY		200
		zip			none			none			50
	end
end


ammo AI_GRPG
	bullet_mass 3
	frndlyTrcrID 1906   
	max_age 11     
	arm_age 0      
	velocity 75 
	error 0
	drag  1
    ai_launch		GS_RPG 
	ai_Launcheffect Effect_RPGMuzz

	turnrate_maxpit  300
	turnrate_maxyaw  300
	boresight_maxang 45   
    heat_det_range 2000

	scorch_id 2
	scar_type 2
    kz_physics 1		

	Mf_Light 100

	kztype rounds_kz_C4  
	kz_minradius 3.0
	kz_maxradius 7.0
	kz_damage		522	
    kz_AI_damage    522 
	impact_damage	128
    impact_AI_damage 128

	light_move     6.0  128 120 80
	light_impact   8.0  255 192 96  0.25

	flag LAWR
	flag NoGravity
	flag forcetracer

	effects_table
		move		effect_rpg		      none				0
		obj        Effect_PRGDirt	explo_ammo_med		200
		dirt       Effect_PRGDirt	explo_dirt			200
		grass      Effect_PRGDirt	explo_ammo_med		200
		snow       Effect_PRGDirt	explo_dirt			200
		cement     Effect_PRGDirt	explo_ammo_med		200
		packeddirt Effect_PRGDirt	explo_dirt			200
		water      effect_waterexp	explo_water_sm		200
		railroad   Effect_PRGDirt	explo_ammo_med		200
		mud        Effect_PRGDirt	explo_ammo_med		200
		ice        Effect_PRGDirt	explo_dirt			200
		quicksand	Effect_PRGDirt	explo_dirt			200
		sand		Effect_PRGDirt	explo_dirt			200
		stone      Effect_PRGDirt	explo_ammo_med		200
		wood       Effect_PRGDirt	explo_ammo_med		200
		metal      Effect_PRGDirt	explo_ammo_med		200
		glass      Effect_PRGDirt	explo_ammo_med		200
		cloth      Effect_PRGDirt	explo_ammo_med		200
		foliage    Effect_PRGDirt	explo_foliage		200
		hmetal     Effect_PRGDirt	explo_ammo_med		200
		flesh      Effect_PRGDirt	explo_ammo_med		200
		player		Effect_PRGDirt	explo_ammo_med		200
		zip			none				by_missile1			50
	end
end

ammo AI_RPG
	bullet_mass 3
	frndlyTrcrID 1873   
	max_age 11     
	arm_age 0      
	velocity 50 
	error 0
	drag  1
    ai_launch		GS_RPG 
	ai_Launcheffect Effect_RPGMuzz

	scorch_id 2
	scar_type 2
    kz_physics 1		

	Mf_Light 100

	kztype rounds_kz_C4  
	kz_minradius 3.0
	kz_maxradius 7.0
	kz_damage		522	
    kz_AI_damage    522 
	impact_damage	128
    impact_AI_damage 128

	light_move     6.0  128 120 80
	light_impact   8.0  255 192 96  0.25

	flag LAWR
	flag NoGravity
	flag forcetracer


	effects_table
		move		effect_rpg		      none				0
		obj        Effect_PRGDirt	explo_ammo_med		200
		dirt       Effect_PRGDirt	explo_dirt			200
		grass      Effect_PRGDirt	explo_ammo_med		200
		snow       Effect_PRGDirt	explo_dirt			200
		cement     Effect_PRGDirt	explo_ammo_med		200
		packeddirt Effect_PRGDirt	explo_dirt			200
		water      effect_waterexp	explo_water_sm		200
		railroad   Effect_PRGDirt	explo_ammo_med		200
		mud        Effect_PRGDirt	explo_ammo_med		200
		ice        Effect_PRGDirt	explo_dirt			200
		quicksand	Effect_PRGDirt	explo_dirt			200
		sand		Effect_PRGDirt	explo_dirt			200
		stone      Effect_PRGDirt	explo_ammo_med		200
		wood       Effect_PRGDirt	explo_ammo_med		200
		metal      Effect_PRGDirt	explo_ammo_med		200
		glass      Effect_PRGDirt	explo_ammo_med		200
		cloth      Effect_PRGDirt	explo_ammo_med		200
		foliage    Effect_PRGDirt	explo_foliage		200
		hmetal     Effect_PRGDirt	explo_ammo_med		200
		flesh      Effect_PRGDirt	explo_ammo_med		200
		player		Effect_PRGDirt	explo_ammo_med		200
		zip			none				by_missile1			50
	end
end

ammo Smine			
	bullet_mass 3
	max_age 7     
	arm_age 0      
	velocity 40 
	error 1
	drag  1
    ai_launch		EXPLO_MINE_SM 

	scorch_id 2
	scar_type 2

	kztype rounds_kz_C4
	kz_minradius 1.0
	kz_maxradius 6.0
	kz_damage 70
	impact_damage 70
    kz_physics 2		


	light_impact   4.0  255 192 96  0.25

    impact_AI_damage 70	
    kz_AI_damage    70 

	effects_table
		move		Effect_SmallMine				none		0
		obj			Effect_SmallMine				none		50
		dirt		Effect_SmallMine				none		50
		grass		Effect_SmallMine				none		50
		snow		Effect_SmallMine				none		50
		cement		Effect_SmallMine				none		50
		packeddirt	Effect_SmallMine				none		50
		water		Effect_SmallMine				none		50
		railroad	Effect_SmallMine				none		50
		mud			Effect_SmallMine				none		50
		ice			Effect_SmallMine				none		50
		quicksand	Effect_SmallMine				none		50
		sand		Effect_SmallMine				none		50
		stone		Effect_SmallMine				none		50
		wood		Effect_SmallMine				none		50
		metal		Effect_SmallMine				none		50
		glass		Effect_SmallMine				none		50
		cloth		Effect_SmallMine				none		50
		foliage		Effect_SmallMine				none		50
		hmetal		Effect_SmallMine				none		50
		flesh		Effect_SmallMine				none		50
		player		Effect_SmallMine				none		50
		zip			Effect_SmallMine				none		50
	end
end

ammo Lmine			
	bullet_mass 3
	max_age 7     
	arm_age 0      
	velocity 40 
	error 1
	drag  1
    ai_launch		EXPLO_MINE_LG 

	scorch_id 2
	scar_type 2

	kztype rounds_kz_C4
	kz_minradius 1.0
	kz_maxradius 8.0
	kz_damage 140
	impact_damage 140
    kz_physics 2		


	light_impact   4.0  255 192 96  0.25

    impact_AI_damage 140	
    kz_AI_damage    140 

	effects_table
		move		Effect_LargeMine	none		0
		obj			none				none		50
		dirt		none				none		50
		grass		none				none		50
		snow		none				none		50
		cement		none				none		50
		packeddirt	none				none		50
		water		none				none		50
		railroad	none				none		50
		mud			none				none		50
		ice			none				none		50
		quicksand	none				none		50
		sand		none				none		50
		stone		none				none		50
		wood		none				none		50
		metal		none				none		50
		glass		none				none		50
		cloth		none				none		50
		foliage		none				none		50
		hmetal		none			    none		50
		flesh		none				none		50
		player		none				none		50
		zip			none				none		50
	end
end

ammo croc		
	bullet_mass 1
	max_age 1     
	velocity 100	
	error .1
	drag  1

	impact_damage 34
    ai_launch		CROCODILE_ATK 	
	flag instantkillzone

	kztype rounds_kz_Slash

	secondary_effect Effect_MeleeBlood

	kz_damage 34
	kz_physics 4
	kz_minradius 0
	kz_maxradius 4
	kz_pieslice	 35		
    impact_AI_damage 34	
    kz_AI_damage    34 

	effects_table
		move		none                none				0
		obj			none				none		15
		dirt		Effect_PistolDirt    none		15
		grass		Effect_PistolGrass   none		15
		snow		Effect_PistolSnow    none		1
		cement		Effect_PistolStone	none		15
		packeddirt	Effect_PistolDirt    none		15
		water		Effect_PistolWater  none		5
		railroad	Effect_PistolMetal   none		15
		mud			Effect_PistolDirt	none		15
		ice			Effect_PistolSnow	none		15
		sand		Effect_PistolSand    none		15
		quicksand	Effect_PistolSand    none		15
		stone		Effect_PistolStone   none		15
		wood		Effect_PistolDirt    none		5
		metal		Effect_PistolMetal   none		15
		glass		Effect_PistolGlass   imp_glass	5
		cloth		Effect_PistolDirt	none		3
		foliage		Effect_PistolGrass 	none		3
		hmetal		Effect_PistolMetal   none		15
		flesh		Effect_PistolBody   none		3
		player		Effect_MeleeBlood	IMP_BULLET_PLAYER		10
		zip			none				none		10
	end
end


ammo AMMO_KNIFE01
	bullet_mass 1
	max_age 1     
	velocity 1		
	error 0
	drag  1

	impact_damage 100
    
	flag instantkillzone
	kztype rounds_kz_Knife
	kz_damage 300
	kz_minradius 1.5
	kz_maxradius 2.75
	kz_pieslice	 35		

	kz_sound IMP_KNIFE_FLESH

    impact_AI_damage 0	
    kz_AI_damage    40 

	effects_table
		move       none						none				0
		obj        none   imp_20mm_dirt		15
		dirt       Effect_PistolDirt		imp_20mm_dirt	15
		grass      Effect_PistolGrass		imp_bullet_grass 15
		snow       Effect_PistolSnow		imp_20mm_dirt	1
		cement     Effect_PistolStone		imp_20mm_dirt	15
		packeddirt Effect_PistolDirt		imp_20mm_dirt	15
		water      Effect_PistolWater		imp_20mm_water	5
		railroad   Effect_PistolMetal		imp_20mm_metal	15
		mud        Effect_PistolDirt		imp_bullet_mud   15
		ice        Effect_PistolSnow		imp_bullet_mud   15
		sand       Effect_PistolSand		IMP_BULLET_SAND	15
		quicksand  Effect_PistolSand		IMP_BULLET_SAND	15
		stone      Effect_PistolStone		imp_20mm_rock	15
		wood       Effect_PistolDirt		imp_20mm_wood	5
		metal      Effect_PistolMetal		imp_20mm_metal	15
		glass      Effect_PistolGlass		imp_glass			5
		cloth      Effect_PistolDirt		IMP_BULLET_CLOTH 3
		foliage    Effect_PistolGrass		imp_20mm_foliage 3
		hmetal     Effect_PistolMetal		imp_20mm_armor	15
		flesh      Effect_PistolBody		IMP_KNIFE_FLESH	3
		player		none					IMP_KNIFE_FLESH	10
		zip			none					wsh_shell_by	10
	end
end

ammo AMMO_BERETTA_9MM
	bullet_mass 175
	max_age 4		
	velocity 381
	error 0
	drag  1
	recoil		15
	scar_type 1
	frndlyTrcrID 4405
	foeTrcrID	 4406
    ai_launch		GS_BERETTA 
	ai_Launcheffect Effect_M4MuzFlashFp
	Mf_Light 100
	impact_damage 38

	kztype rounds_kz_C4  
	kz_damage 0
	kz_minradius 2.5
	kz_maxradius 2.5

    flag muzzle1  

    impact_AI_damage 13	
    kz_AI_damage    0 

	effects_table
		move		none					none				0
		obj			Effect_PistolMetal		IMP_BULLET_DIRT		15
		dirt		Effect_PistolDirt		IMP_BULLET_DIRT		15
		grass		Effect_PistolGrass		imp_bullet_grass	15
		snow		Effect_PistolSnow		IMP_BULLET_DIRT		1
		cement		Effect_PistolStone		IMP_BULLET_ROCK		15
		packeddirt	Effect_PistolDirt		imp_20mm_dirt		15
		water		Effect_PistolWater		IMP_BULLET_WATER	5
		railroad	Effect_PistolMetal		IMP_BULLET_METAL	15
		mud			Effect_PistolDirt		imp_bullet_mud		15
		ice			Effect_PistolSnow		imp_bullet_mud		15
		sand		Effect_PistolSand		IMP_BULLET_SAND		15
		quicksand	Effect_PistolSand		IMP_BULLET_SAND		15
		stone		Effect_PistolStone		IMP_BULLET_ROCK		15
		wood		Effect_PistolWood		IMP_BULLET_WOOD		5
		metal		Effect_PistolMetal		IMP_BULLET_METAL	15
		glass		Effect_PistolGlass		imp_glass			5
		cloth		Effect_PistolDirt		IMP_BULLET_CLOTH		3
		foliage		Effect_PistolFoliage	IMP_BULLET_FOLIAGE	3
		hmetal		Effect_PistolMetal		IMP_BULLET_ARMOR	15
		flesh		Effect_PistolBody		IMP_BULLET_FLESH	3
		player		Effect_PistolBody		IMP_BULLET_PLAYER	10
		zip			none					WSH_BULLET_BY2		10
	end
end

ammo AMMO_COLT_45
	bullet_mass 1
	max_age 8     
	velocity 242
	error 0
	drag  1
	scar_type 1
	recoil		17
	frndlyTrcrID 4405
	foeTrcrID	 4406
    ai_launch		GS_45 
	ai_Launcheffect Effect_M4MuzFlashFp
	Mf_Light 100
	impact_damage 51

	kztype rounds_kz_C4  
	kz_damage 0
	kz_minradius 2.5
	kz_maxradius 2.5

    flag muzzle1  

    impact_AI_damage 18	
    kz_AI_damage    0 

	effects_table
		move		none					none				0
		obj			Effect_PistolMetal		IMP_BULLET_DIRT		15
		dirt		Effect_PistolDirt		IMP_BULLET_DIRT		15
		grass		Effect_PistolGrass		imp_bullet_grass	15
		snow		Effect_PistolSnow		IMP_BULLET_DIRT		1
		cement		Effect_PistolStone		IMP_BULLET_ROCK		15
		packeddirt	Effect_PistolDirt		imp_20mm_dirt		15
		water		Effect_PistolWater		IMP_BULLET_WATER	5
		railroad	Effect_PistolMetal		IMP_BULLET_METAL	15
		mud			Effect_PistolDirt		imp_bullet_mud		15
		ice			Effect_PistolSnow		imp_bullet_mud		15
		sand		Effect_PistolSand		IMP_BULLET_SAND		15
		quicksand	Effect_PistolSand		IMP_BULLET_SAND		15
		stone		Effect_PistolStone		IMP_BULLET_ROCK		15
		wood		Effect_PistolWood		IMP_BULLET_WOOD		5
		metal		Effect_PistolMetal		IMP_BULLET_METAL	15
		glass		Effect_PistolGlass		imp_glass			5
		cloth		Effect_PistolDirt		IMP_BULLET_CLOTH		3
		foliage		Effect_PistolFoliage	IMP_BULLET_FOLIAGE	3
		hmetal		Effect_PistolMetal		IMP_BULLET_ARMOR	15
		flesh		Effect_PistolBody		IMP_BULLET_FLESH	3
		player		Effect_PistolBody		IMP_BULLET_PLAYER	10
		zip			none					WSH_BULLET_BY2		10
	end
end

ammo AMMO_SHOTGUN
	bullet_mass 1
	max_age 3     
	velocity 400
	error 0
	drag  1
	recoil		101
	scorch_id 1
	scar_type 1

	kztype rounds_kz_C4  
	kz_damage 0
	kz_minradius 2.5
	kz_maxradius 2.5

	impact_damage 35
    flag muzzle1 
	flag shotgun
    ai_launch		GS_12GAGE 	
	Mf_Light 100
	spread_count	9
	kz_pieslice	 2		
    impact_AI_damage 12	
    kz_AI_damage    0 

	effects_table
		dirt       Effect_SGvDirt			IMP_12GAGE_DIRT		15
		grass      Effect_SGvGrass			IMP_12GAGE_DIRT		15
		snow       Effect_SGvSnow			IMP_12GAGE_DIRT		1
		cement     Effect_SGvStone			IMP_12GAGE_ROCK		15
		packeddirt Effect_SGvDirt			IMP_12GAGE_DIRT		15
		water      Effect_SGvWater			IMP_12GAGE_WATER	5
		railroad   Effect_SGvMetal			IMP_12GAGE_METAL	15
		mud        Effect_SGvDirt			IMP_12GAGE_DIRT		15
		ice        Effect_SGvSnow			IMP_12GAGE_DIRT		15
		sand       Effect_SGvSand			IMP_12GAGE_SAND		15
		quicksand  Effect_SGvSand			IMP_12GAGE_SAND		15
		stone      Effect_SGvStone			IMP_12GAGE_ROCK		15
		wood       Effect_SGvDirt			IMP_BULLET_WOOD		5
		metal      Effect_SGvMetal			IMP_12GAGE_METAL	15
		glass      Effect_SGvGlass			imp_glass			5
		cloth      Effect_SGvDirt			IMP_12G_CLOTH		3
		foliage    Effect_SGvGrass			IMP_12GAGE_FOLG		3
		hmetal     Effect_SGvMetal			IMP_12GAGE_METAL	15
		flesh      Effect_SGvBody			IMP_12GAGE_FLESH	3
		player	   Effect_SGvBody			IMP_BULLET_PLAYER	10
		zip		   Effect_SGvBody			WSH_12GAGE_BY		10
	end
end

ammo 12GA
	bullet_mass 1
	max_age 3
	velocity 350
	error 0
	drag  1
	recoil		90
	scorch_id 1
	scar_type 1

	kztype rounds_kz_C4  
	kz_damage 0
	kz_minradius 2.5
	kz_maxradius 2.5

	impact_damage 20
    flag muzzle1 
	flag shotgun
    ai_launch		GS_12GAGE 	
	Mf_Light 100
	spread_count	12
	kz_pieslice	 4		
    impact_AI_damage 12	
    kz_AI_damage    0 

	effects_table
		dirt       Effect_SGvDirt			IMP_12GAGE_DIRT		15
		grass      Effect_SGvGrass			IMP_12GAGE_DIRT		15
		snow       Effect_SGvSnow			IMP_12GAGE_DIRT		1
		cement     Effect_SGvStone			IMP_12GAGE_ROCK		15
		packeddirt Effect_SGvDirt			IMP_12GAGE_DIRT		15
		water      Effect_SGvWater			IMP_12GAGE_WATER	5
		railroad   Effect_SGvMetal			IMP_12GAGE_METAL	15
		mud        Effect_SGvDirt			IMP_12GAGE_DIRT		15
		ice        Effect_SGvSnow			IMP_12GAGE_DIRT		15
		sand       Effect_SGvSand			IMP_12GAGE_SAND		15
		quicksand  Effect_SGvSand			IMP_12GAGE_SAND		15
		stone      Effect_SGvStone			IMP_12GAGE_ROCK		15
		wood       Effect_SGvDirt			IMP_BULLET_WOOD		5
		metal      Effect_SGvMetal			IMP_12GAGE_METAL	15
		glass      Effect_SGvGlass			imp_glass			5
		cloth      Effect_SGvDirt			IMP_12G_CLOTH		3
		foliage    Effect_SGvGrass			IMP_12GAGE_FOLG		3
		hmetal     Effect_SGvMetal			IMP_12GAGE_METAL	15
		flesh      Effect_SGvBody			IMP_12GAGE_FLESH	3
		player	   Effect_SGvBody			IMP_BULLET_PLAYER	10
		zip		   Effect_SGvBody			WSH_12GAGE_BY		10
	end
end

ammo AMMO_CAR15_556MM
	bullet_mass 68
	max_age 3
	arm_age 0
	velocity 910
	error 0
	drag  1
	recoil		13
	scar_type 1
	frndlyTrcrID 4405
	foeTrcrID	 4406
	impact_damage 38
    flag muzzle1  
    ai_launch		GS_CAR15AI 	
	Mf_Light 100
	kztype rounds_kz_C4  
	kz_damage 0
	kz_minradius 2.5
	kz_maxradius 2.5

    impact_AI_damage 18	
    kz_AI_damage    0 

	effects_table
		move		none					none				0
		obj			Effect_PistolMetal		IMP_BULLET_DIRT		15
		dirt		Effect_PistolDirt		IMP_BULLET_DIRT		15
		grass		Effect_PistolGrass		imp_bullet_grass	15
		snow		Effect_PistolSnow		IMP_BULLET_DIRT		1
		cement		Effect_PistolStone		IMP_BULLET_ROCK		15
		packeddirt	Effect_PistolDirt		imp_20mm_dirt		15
		water		Effect_PistolWater		IMP_BULLET_WATER	5
		railroad	Effect_PistolMetal		IMP_BULLET_METAL	15
		mud			Effect_PistolDirt		imp_bullet_mud		15
		ice			Effect_PistolSnow		imp_bullet_mud		15
		sand		Effect_PistolSand		IMP_BULLET_SAND		15
		quicksand	Effect_PistolSand		IMP_BULLET_SAND		15
		stone		Effect_PistolStone		IMP_BULLET_ROCK		15
		wood		Effect_PistolWood		IMP_BULLET_WOOD		5
		metal		Effect_PistolMetal		IMP_BULLET_METAL	15
		glass		Effect_PistolGlass		imp_glass			5
		cloth		Effect_PistolDirt		IMP_BULLET_CLOTH		3
		foliage		Effect_PistolFoliage	IMP_BULLET_FOLIAGE	3
		hmetal		Effect_PistolMetal		IMP_BULLET_ARMOR	15
		flesh		Effect_PistolBody		IMP_BULLET_FLESH	3
		player		Effect_PistolBody		IMP_BULLET_PLAYER	10
		zip			none					WSH_BULLET_BY2		10
	end
end

ammo AMMO_C723_556MM
	bullet_mass 68
	max_age 3 
	arm_age 0
	velocity 868
	error 0
	drag  1
	recoil		14
	scar_type 1
	frndlyTrcrID 4405
	foeTrcrID	 4406
	impact_damage 45
    flag muzzle1
	flag silenced
    ai_launch		GS_CAR15AI 	
	Mf_Light 100
	kztype rounds_kz_C4  
	kz_damage 0
	kz_minradius 2.5
	kz_maxradius 2.5

    impact_AI_damage 18	
    kz_AI_damage    0 

	effects_table
		move		none					none				0
		obj			Effect_PistolMetal		IMP_BULLET_DIRT		15
		dirt		Effect_PistolDirt		IMP_BULLET_DIRT		15
		grass		Effect_PistolGrass		imp_bullet_grass	15
		snow		Effect_PistolSnow		IMP_BULLET_DIRT		1
		cement		Effect_PistolStone		IMP_BULLET_ROCK		15
		packeddirt	Effect_PistolDirt		imp_20mm_dirt		15
		water		Effect_PistolWater		IMP_BULLET_WATER	5
		railroad	Effect_PistolMetal		IMP_BULLET_METAL	15
		mud			Effect_PistolDirt		imp_bullet_mud		15
		ice			Effect_PistolSnow		imp_bullet_mud		15
		sand		Effect_PistolSand		IMP_BULLET_SAND		15
		quicksand	Effect_PistolSand		IMP_BULLET_SAND		15
		stone		Effect_PistolStone		IMP_BULLET_ROCK		15
		wood		Effect_PistolWood		IMP_BULLET_WOOD		5
		metal		Effect_PistolMetal		IMP_BULLET_METAL	15
		glass		Effect_PistolGlass		imp_glass			5
		cloth		Effect_PistolDirt		IMP_BULLET_CLOTH		3
		foliage		Effect_PistolFoliage	IMP_BULLET_FOLIAGE	3
		hmetal		Effect_PistolMetal		IMP_BULLET_ARMOR	15
		flesh		Effect_PistolBody		IMP_BULLET_FLESH	3
		player		Effect_PistolBody		IMP_BULLET_PLAYER	10
		zip			none					WSH_BULLET_BY2		10
	end
end

ammo AMMO_G36_556MM
	bullet_mass 68
	max_age 3 
	arm_age 0
	velocity 947
	error 0
	drag  1
	recoil		10
	scar_type 1
	frndlyTrcrID 4405
	foeTrcrID	 4406
	impact_damage 45
    flag muzzle1
	flag silenced
    ai_launch		GS_CAR15AI 	
	Mf_Light 100
	kztype rounds_kz_C4  
	kz_damage 0
	kz_minradius 2.5
	kz_maxradius 2.5

    impact_AI_damage 18	
    kz_AI_damage    0 

	effects_table
		move		none					none				0
		obj			Effect_PistolMetal		IMP_BULLET_DIRT		15
		dirt		Effect_PistolDirt		IMP_BULLET_DIRT		15
		grass		Effect_PistolGrass		imp_bullet_grass	15
		snow		Effect_PistolSnow		IMP_BULLET_DIRT		1
		cement		Effect_PistolStone		IMP_BULLET_ROCK		15
		packeddirt	Effect_PistolDirt		imp_20mm_dirt		15
		water		Effect_PistolWater		IMP_BULLET_WATER	5
		railroad	Effect_PistolMetal		IMP_BULLET_METAL	15
		mud			Effect_PistolDirt		imp_bullet_mud		15
		ice			Effect_PistolSnow		imp_bullet_mud		15
		sand		Effect_PistolSand		IMP_BULLET_SAND		15
		quicksand	Effect_PistolSand		IMP_BULLET_SAND		15
		stone		Effect_PistolStone		IMP_BULLET_ROCK		15
		wood		Effect_PistolWood		IMP_BULLET_WOOD		5
		metal		Effect_PistolMetal		IMP_BULLET_METAL	15
		glass		Effect_PistolGlass		imp_glass			5
		cloth		Effect_PistolDirt		IMP_BULLET_CLOTH		3
		foliage		Effect_PistolFoliage	IMP_BULLET_FOLIAGE	3
		hmetal		Effect_PistolMetal		IMP_BULLET_ARMOR	15
		flesh		Effect_PistolBody		IMP_BULLET_FLESH	3
		player		Effect_PistolBody		IMP_BULLET_PLAYER	10
		zip			none					WSH_BULLET_BY2		10
	end
end

ammo AMMO_M16_556MM
	bullet_mass 1
	max_age 3  
	arm_age 0
	velocity 975
	error 0
	drag  1 
	recoil		12
	scar_type 1
	frndlyTrcrID 4405
	foeTrcrID	 4406
	impact_damage 50
    flag muzzle1  
    ai_launch		GS_M16 	
	Mf_Light 100
	kztype rounds_kz_C4  
	kz_damage 0
	kz_minradius 2.5
	kz_maxradius 2.5

    impact_AI_damage 18	
    kz_AI_damage    0 

	effects_table
		move		none					none				0
		obj			Effect_PistolMetal		IMP_BULLET_DIRT		15
		dirt		Effect_PistolDirt		IMP_BULLET_DIRT		15
		grass		Effect_PistolGrass		imp_bullet_grass	15
		snow		Effect_PistolSnow		IMP_BULLET_DIRT		1
		cement		Effect_PistolStone		IMP_BULLET_ROCK		15
		packeddirt	Effect_PistolDirt		imp_20mm_dirt		15
		water		Effect_PistolWater		IMP_BULLET_WATER	5
		railroad	Effect_PistolMetal		IMP_BULLET_METAL	15
		mud			Effect_PistolDirt		imp_bullet_mud		15
		ice			Effect_PistolSnow		imp_bullet_mud		15
		sand		Effect_PistolSand		IMP_BULLET_SAND		15
		quicksand	Effect_PistolSand		IMP_BULLET_SAND		15
		stone		Effect_PistolStone		IMP_BULLET_ROCK		15
		wood		Effect_PistolWood		IMP_BULLET_WOOD		5
		metal		Effect_PistolMetal		IMP_BULLET_METAL	15
		glass		Effect_PistolGlass		imp_glass			5
		cloth		Effect_PistolDirt		IMP_BULLET_CLOTH		3
		foliage		Effect_PistolFoliage	IMP_BULLET_FOLIAGE	3
		hmetal		Effect_PistolMetal		IMP_BULLET_ARMOR	15
		flesh		Effect_PistolBody		IMP_BULLET_FLESH	3
		player		Effect_PistolBody		IMP_BULLET_PLAYER	10
		zip			none					WSH_BULLET_BY2		10
	end
end

ammo AMMO_MP5_9MM
	bullet_mass 124
	max_age 6    
	arm_age 0
	velocity 285
	error 0
	drag  1
	recoil		3
	scar_type 1
	frndlyTrcrID 4405
	foeTrcrID	 4406
	Mf_Light 100
    flag muzzle1  
	flag silenced
    ai_launch		GS_MP5SUP_AI 	

	impact_damage 30

	kztype rounds_kz_C4  
	kz_damage 0
	kz_minradius 2.5
	kz_maxradius 2.5

    impact_AI_damage 13	
    kz_AI_damage    0 

	effects_table
		move		none					none				0
		obj			Effect_PistolMetal		IMP_BULLET_DIRT		15
		dirt		Effect_PistolDirt		IMP_BULLET_DIRT		15
		grass		Effect_PistolGrass		imp_bullet_grass	15
		snow		Effect_PistolSnow		IMP_BULLET_DIRT		1
		cement		Effect_PistolStone		IMP_BULLET_ROCK		15
		packeddirt	Effect_PistolDirt		imp_20mm_dirt		15
		water		Effect_PistolWater		IMP_BULLET_WATER	5
		railroad	Effect_PistolMetal		IMP_BULLET_METAL	15
		mud			Effect_PistolDirt		imp_bullet_mud		15
		ice			Effect_PistolSnow		imp_bullet_mud		15
		sand		Effect_PistolSand		IMP_BULLET_SAND		15
		quicksand	Effect_PistolSand		IMP_BULLET_SAND		15
		stone		Effect_PistolStone		IMP_BULLET_ROCK		15
		wood		Effect_PistolWood		IMP_BULLET_WOOD		5
		metal		Effect_PistolMetal		IMP_BULLET_METAL	15
		glass		Effect_PistolGlass		imp_glass			5
		cloth		Effect_PistolDirt		IMP_BULLET_CLOTH		3
		foliage		Effect_PistolFoliage	IMP_BULLET_FOLIAGE	3
		hmetal		Effect_PistolMetal		IMP_BULLET_ARMOR	15
		flesh		Effect_PistolBody		IMP_BULLET_FLESH	3
		player		Effect_PistolBody		IMP_BULLET_PLAYER	10
		zip			none					WSH_BULLET_BY2		10
	end
end

ammo AMMO_SAW_556MM
	bullet_mass 62
	max_age 3   
	arm_age 0
	penetration 1
	velocity 976
	error 0
	drag  1
	recoil		7
	scar_type 1
	frndlyTrcrID 4405
	foeTrcrID	 4406
	Mf_Light 100	
    flag muzzle1  
    ai_launch		GS_SAW 	

	impact_damage 45

	kztype rounds_kz_C4  
	kz_damage 0
	kz_minradius 2.0
	kz_maxradius 2.0

    impact_AI_damage 18	
    kz_AI_damage    0 

	effects_table
		move		none					none				0
		obj			Effect_PistolMetal		IMP_BULLET_DIRT		15
		dirt		Effect_PistolDirt		IMP_BULLET_DIRT		15
		grass		Effect_PistolGrass		imp_bullet_grass	15
		snow		Effect_PistolSnow		IMP_BULLET_DIRT		1
		cement		Effect_PistolStone		IMP_BULLET_ROCK		15
		packeddirt	Effect_PistolDirt		imp_20mm_dirt		15
		water		Effect_PistolWater		IMP_BULLET_WATER	5
		railroad	Effect_PistolMetal		IMP_BULLET_METAL	15
		mud			Effect_PistolDirt		imp_bullet_mud		15
		ice			Effect_PistolSnow		imp_bullet_mud		15
		sand		Effect_PistolSand		IMP_BULLET_SAND		15
		quicksand	Effect_PistolSand		IMP_BULLET_SAND		15
		stone		Effect_PistolStone		IMP_BULLET_ROCK		15
		wood		Effect_PistolWood		IMP_BULLET_WOOD		5
		metal		Effect_PistolMetal		IMP_BULLET_METAL	15
		glass		Effect_PistolGlass		imp_glass			5
		cloth		Effect_PistolDirt		IMP_BULLET_CLOTH		3
		foliage		Effect_PistolFoliage	IMP_BULLET_FOLIAGE	3
		hmetal		Effect_PistolMetal		IMP_BULLET_ARMOR	15
		flesh		Effect_PistolBody		IMP_BULLET_FLESH	3
		player		Effect_PistolBody		IMP_BULLET_PLAYER	10
		zip			none					WSH_BULLET_BY2		10
	end
end

ammo AMMO_M60_762MM
	bullet_mass 147
	max_age 3  
	arm_age 0
	penetration 1
	velocity 853
	error 0
	drag  1
	recoil		16
	scar_type 1
	frndlyTrcrID 4405
	foeTrcrID	 4406
	Mf_Light 100
    flag muzzle1  
    ai_launch		GS_M60 	

	impact_damage 167

	kztype rounds_kz_C4  
	kz_damage 0
	kz_minradius 2.0
	kz_maxradius 2.0

    impact_AI_damage 38	
    kz_AI_damage    0 

	effects_table
		move		none					none				0
		obj			Effect_PistolMetal		IMP_BULLET_DIRT		15
		dirt		Effect_PistolDirt		IMP_BULLET_DIRT		15
		grass		Effect_PistolGrass		imp_bullet_grass	15
		snow		Effect_PistolSnow		IMP_BULLET_DIRT		1
		cement		Effect_PistolStone		IMP_BULLET_ROCK		15
		packeddirt	Effect_PistolDirt		imp_20mm_dirt		15
		water		Effect_PistolWater		IMP_BULLET_WATER	5
		railroad	Effect_PistolMetal		IMP_BULLET_METAL	15
		mud			Effect_PistolDirt		imp_bullet_mud		15
		ice			Effect_PistolSnow		imp_bullet_mud		15
		sand		Effect_PistolSand		IMP_BULLET_SAND		15
		quicksand	Effect_PistolSand		IMP_BULLET_SAND		15
		stone		Effect_PistolStone		IMP_BULLET_ROCK		15
		wood		Effect_PistolWood		IMP_BULLET_WOOD		5
		metal		Effect_PistolMetal		IMP_BULLET_METAL	15
		glass		Effect_PistolGlass		imp_glass			5
		cloth		Effect_PistolDirt		IMP_BULLET_CLOTH		3
		foliage		Effect_PistolFoliage	IMP_BULLET_FOLIAGE	3
		hmetal		Effect_PistolMetal		IMP_BULLET_ARMOR	15
		flesh		Effect_PistolBody		IMP_BULLET_FLESH	3
		player		Effect_PistolBody		IMP_BULLET_PLAYER	10
		zip			none					WSH_BULLET_BY2		10
	end
end

ammo AMMO_G3_762MM
	bullet_mass 145
	max_age 3
	arm_age 0
	penetration 1
	velocity 800
	error 0
	drag  1
	recoil		31
	scar_type 1
	frndlyTrcrID 4405
	foeTrcrID	 4406
	Mf_Light 100
    flag muzzle1  
    ai_launch		GS_M60 	

	impact_damage 167

	kztype rounds_kz_C4  
	kz_damage 0
	kz_minradius 2.0
	kz_maxradius 2.0

    impact_AI_damage 38	
    kz_AI_damage    0 

	effects_table
		move		none					none				0
		obj			Effect_PistolMetal		IMP_BULLET_DIRT		15
		dirt		Effect_PistolDirt		IMP_BULLET_DIRT		15
		grass		Effect_PistolGrass		imp_bullet_grass	15
		snow		Effect_PistolSnow		IMP_BULLET_DIRT		1
		cement		Effect_PistolStone		IMP_BULLET_ROCK		15
		packeddirt	Effect_PistolDirt		imp_20mm_dirt		15
		water		Effect_PistolWater		IMP_BULLET_WATER	5
		railroad	Effect_PistolMetal		IMP_BULLET_METAL	15
		mud			Effect_PistolDirt		imp_bullet_mud		15
		ice			Effect_PistolSnow		imp_bullet_mud		15
		sand		Effect_PistolSand		IMP_BULLET_SAND		15
		quicksand	Effect_PistolSand		IMP_BULLET_SAND		15
		stone		Effect_PistolStone		IMP_BULLET_ROCK		15
		wood		Effect_PistolWood		IMP_BULLET_WOOD		5
		metal		Effect_PistolMetal		IMP_BULLET_METAL	15
		glass		Effect_PistolGlass		imp_glass			5
		cloth		Effect_PistolDirt		IMP_BULLET_CLOTH		3
		foliage		Effect_PistolFoliage	IMP_BULLET_FOLIAGE	3
		hmetal		Effect_PistolMetal		IMP_BULLET_ARMOR	15
		flesh		Effect_PistolBody		IMP_BULLET_FLESH	3
		player		Effect_PistolBody		IMP_BULLET_PLAYER	10
		zip			none					WSH_BULLET_BY2		10
	end
end


ammo AMMO_RPK_762x39
	bullet_mass 122
	max_age 3
	arm_age 0
	penetration 1
	velocity 745
	error 0
	drag  1
	recoil		16
	scar_type 1
	frndlyTrcrID 4405
	foeTrcrID	 4406
	Mf_Light 100
    flag muzzle1  
    ai_launch		GS_MAG58 	

	impact_damage 123

	kztype rounds_kz_C4  
	kz_damage 0
	kz_minradius 2.0
	kz_maxradius 2.0

    impact_AI_damage 38	
    kz_AI_damage    0 

	effects_table
		move		none					none				0
		obj			Effect_PistolMetal		IMP_BULLET_DIRT		15
		dirt		Effect_PistolDirt		IMP_BULLET_DIRT		15
		grass		Effect_PistolGrass		imp_bullet_grass	15
		snow		Effect_PistolSnow		IMP_BULLET_DIRT		1
		cement		Effect_PistolStone		IMP_BULLET_ROCK		15
		packeddirt	Effect_PistolDirt		imp_20mm_dirt		15
		water		Effect_PistolWater		IMP_BULLET_WATER	5
		railroad	Effect_PistolMetal		IMP_BULLET_METAL	15
		mud			Effect_PistolDirt		imp_bullet_mud		15
		ice			Effect_PistolSnow		imp_bullet_mud		15
		sand		Effect_PistolSand		IMP_BULLET_SAND		15
		quicksand	Effect_PistolSand		IMP_BULLET_SAND		15
		stone		Effect_PistolStone		IMP_BULLET_ROCK		15
		wood		Effect_PistolWood		IMP_BULLET_WOOD		5
		metal		Effect_PistolMetal		IMP_BULLET_METAL	15
		glass		Effect_PistolGlass		imp_glass			5
		cloth		Effect_PistolDirt		IMP_BULLET_CLOTH		3
		foliage		Effect_PistolFoliage	IMP_BULLET_FOLIAGE	3
		hmetal		Effect_PistolMetal		IMP_BULLET_ARMOR	15
		flesh		Effect_PistolBody		IMP_BULLET_FLESH	3
		player		Effect_PistolBody		IMP_BULLET_PLAYER	10
		zip			none					WSH_BULLET_BY2		10
	end
end

ammo AMMO_M21_762HPBT
	bullet_mass 135
	max_age 3
	velocity 853
	error 0
	drag  1
	recoil		28
	scar_type 1
	frndlyTrcrID 4405
	foeTrcrID	 4406
	Mf_Light 100
    flag muzzle1  
    ai_launch		GS_M21N 	

	impact_damage 201

	kztype rounds_kz_C4  
	kz_damage 0
	kz_minradius 2.5
	kz_maxradius 2.5

    impact_AI_damage 35	
    kz_AI_damage    0 

	effects_table
		move		none					none				0
		obj			Effect_PistolMetal		IMP_BULLET_DIRT		15
		dirt		Effect_PistolDirt		IMP_BULLET_DIRT		15
		grass		Effect_PistolGrass		imp_bullet_grass	15
		snow		Effect_PistolSnow		IMP_BULLET_DIRT		1
		cement		Effect_PistolStone		IMP_BULLET_ROCK		15
		packeddirt	Effect_PistolDirt		imp_20mm_dirt		15
		water		Effect_PistolWater		IMP_BULLET_WATER	5
		railroad	Effect_PistolMetal		IMP_BULLET_METAL	15
		mud			Effect_PistolDirt		imp_bullet_mud		15
		ice			Effect_PistolSnow		imp_bullet_mud		15
		sand		Effect_PistolSand		IMP_BULLET_SAND		15
		quicksand	Effect_PistolSand		IMP_BULLET_SAND		15
		stone		Effect_PistolStone		IMP_BULLET_ROCK		15
		wood		Effect_PistolWood		IMP_BULLET_WOOD		5
		metal		Effect_PistolMetal		IMP_BULLET_METAL	15
		glass		Effect_PistolGlass		imp_glass			5
		cloth		Effect_PistolDirt		IMP_BULLET_CLOTH		3
		foliage		Effect_PistolFoliage	IMP_BULLET_FOLIAGE	3
		hmetal		Effect_PistolMetal		IMP_BULLET_ARMOR	15
		flesh		Effect_PistolBody		IMP_BULLET_FLESH	3
		player		Effect_PistolBody		IMP_BULLET_PLAYER	10
		zip			none					WSH_BULLET_BY		10
	end
end

ammo AMMO_DRAGUNOV_mm
	bullet_mass 160
	max_age 3
	velocity 797
	error 0
	drag  1
	recoil		33
	scar_type 1
	frndlyTrcrID 4405
	foeTrcrID	 4406
	Mf_Light 100
    flag muzzle1  
    ai_launch		GS_M21N 	

	impact_damage 206

	kztype rounds_kz_C4  
	kz_damage 0
	kz_minradius 2.5
	kz_maxradius 2.5

    impact_AI_damage 35	
    kz_AI_damage    0 

	effects_table
		move		none					none				0
		obj			Effect_PistolMetal		IMP_BULLET_DIRT		15
		dirt		Effect_PistolDirt		IMP_BULLET_DIRT		15
		grass		Effect_PistolGrass		imp_bullet_grass	15
		snow		Effect_PistolSnow		IMP_BULLET_DIRT		1
		cement		Effect_PistolStone		IMP_BULLET_ROCK		15
		packeddirt	Effect_PistolDirt		imp_20mm_dirt		15
		water		Effect_PistolWater		IMP_BULLET_WATER	5
		railroad	Effect_PistolMetal		IMP_BULLET_METAL	15
		mud			Effect_PistolDirt		imp_bullet_mud		15
		ice			Effect_PistolSnow		imp_bullet_mud		15
		sand		Effect_PistolSand		IMP_BULLET_SAND		15
		quicksand	Effect_PistolSand		IMP_BULLET_SAND		15
		stone		Effect_PistolStone		IMP_BULLET_ROCK		15
		wood		Effect_PistolWood		IMP_BULLET_WOOD		5
		metal		Effect_PistolMetal		IMP_BULLET_METAL	15
		glass		Effect_PistolGlass		imp_glass			5
		cloth		Effect_PistolDirt		IMP_BULLET_CLOTH		3
		foliage		Effect_PistolFoliage	IMP_BULLET_FOLIAGE	3
		hmetal		Effect_PistolMetal		IMP_BULLET_ARMOR	15
		flesh		Effect_PistolBody		IMP_BULLET_FLESH	3
		player		Effect_PistolBody		IMP_BULLET_PLAYER	10
		zip			none					WSH_BULLET_BY		10
	end
end


ammo AMMO_M24_762HPBT
	bullet_mass 185
	max_age 3
	velocity 868
	error 0
	drag  1
	recoil		27
	scar_type 1
	frndlyTrcrID 4405
	foeTrcrID	 4406
	Mf_Light 100
    flag muzzle1  
    ai_launch		GS_M24 	

	impact_damage 217
	
	kztype rounds_kz_C4  
	kz_damage 0
	kz_minradius 2.5
	kz_maxradius 2.5

    impact_AI_damage 35	
    kz_AI_damage    0 

	effects_table
		move		none					none				0
		obj			Effect_PistolMetal		IMP_BULLET_DIRT		15
		dirt		Effect_PistolDirt		IMP_BULLET_DIRT		15
		grass		Effect_PistolGrass		imp_bullet_grass	15
		snow		Effect_PistolSnow		IMP_BULLET_DIRT		1
		cement		Effect_PistolStone		IMP_BULLET_ROCK		15
		packeddirt	Effect_PistolDirt		imp_20mm_dirt		15
		water		Effect_PistolWater		IMP_BULLET_WATER	5
		railroad	Effect_PistolMetal		IMP_BULLET_METAL	15
		mud			Effect_PistolDirt		imp_bullet_mud		15
		ice			Effect_PistolSnow		imp_bullet_mud		15
		sand		Effect_PistolSand		IMP_BULLET_SAND		15
		quicksand	Effect_PistolSand		IMP_BULLET_SAND		15
		stone		Effect_PistolStone		IMP_BULLET_ROCK		15
		wood		Effect_PistolWood		IMP_BULLET_WOOD		5
		metal		Effect_PistolMetal		IMP_BULLET_METAL	15
		glass		Effect_PistolGlass		imp_glass			5
		cloth		Effect_PistolDirt		IMP_BULLET_CLOTH		3
		foliage		Effect_PistolFoliage	IMP_BULLET_FOLIAGE	3
		hmetal		Effect_PistolMetal		IMP_BULLET_ARMOR	15
		flesh		Effect_PistolBody		IMP_BULLET_FLESH	3
		player		Effect_PistolBody		IMP_BULLET_PLAYER	10
		zip			none					WSH_BULLET_BY		10
	end
end

ammo AMMO_BARRET_50CAL
	bullet_mass 647
	max_age 3.5
	velocity 853
	error 0
	drag  1
	recoil		75
	scar_type 1
	frndlyTrcrID 4405
	foeTrcrID	 4406
	Mf_Light 100
    flag muzzle1  
    ai_launch		GS_BARRET 	

	impact_damage 600

	kztype rounds_kz_C4  
	kz_damage 50
	kz_minradius 0
	kz_maxradius 0.25

    impact_AI_damage 67	
    kz_AI_damage    0 

	effects_table
		move       none						none				0
		obj        Effect_FX50CalObj		IMP_BULLET_DIRT		15
		dirt       Effect_FX50CalDirt		IMP_BULLET_DIRT		15
		grass      Effect_FX50CalGrass		imp_bullet_grass	15
		snow       Effect_FX50CalDirt		IMP_BULLET_DIRT		1
		cement     Effect_FX50CalStone		IMP_BULLET_ROCK		15
		packeddirt Effect_FX50CalDirt		imp_20mm_dirt		15
		water      Effect_WatersplshMed		IMP_BULLET_WATER	5
		railroad   Effect_FX50CalMetal		IMP_BULLET_METAL	15
		mud        Effect_FX50CalDirt		imp_bullet_mud		15
		ice        Effect_PistolSnow		imp_bullet_mud		15
		sand       Effect_FX50CalSand		IMP_BULLET_SAND		15
		quicksand  Effect_FX50CalSand		IMP_BULLET_SAND		15
		stone      Effect_FX50CalStone		IMP_BULLET_ROCK		15
		wood       Effect_FX50CalWood		IMP_BULLET_WOOD		5
		metal      Effect_FX50CalMetal		IMP_BULLET_METAL	15
		glass      Effect_FX50CalGlass		imp_glass			5
		cloth      Effect_FX50CalObj		IMP_BULLET_CLOTH	3
		foliage    Effect_FX50CalWoodF		IMP_BULLET_FOLIAGE	3
		hmetal     Effect_FX50CalMetal		IMP_BULLET_ARMOR	15
		flesh      Effect_FX50CalBody		IMP_BULLET_FLESH	3
		player		Effect_FX50CalBody		imp_bullet_flesh	10
		zip			none					wsh_bullet_by		10
	end
end

ammo AMMO_WINCHESTER300_300MAG
	bullet_mass 200
	max_age 3
	velocity 923
	error 0
	drag  1
	recoil		37
	scar_type 1
	frndlyTrcrID 4405
	foeTrcrID	 4406
	Mf_Light 100
    flag muzzle1  
    ai_launch		GS_W300MAG 	

	impact_damage 264

	kztype rounds_kz_C4  
	kz_damage 0
	kz_minradius 2.5
	kz_maxradius 2.5

    impact_AI_damage 43	
    kz_AI_damage    0 

	effects_table
		move		none					none				0
		obj			Effect_PistolMetal		IMP_BULLET_DIRT		15
		dirt		Effect_PistolDirt		IMP_BULLET_DIRT		15
		grass		Effect_PistolGrass		imp_bullet_grass	15
		snow		Effect_PistolSnow		IMP_BULLET_DIRT		1
		cement		Effect_PistolStone		IMP_BULLET_ROCK		15
		packeddirt	Effect_PistolDirt		imp_20mm_dirt		15
		water		Effect_PistolWater		IMP_BULLET_WATER	5
		railroad	Effect_PistolMetal		IMP_BULLET_METAL	15
		mud			Effect_PistolDirt		imp_bullet_mud		15
		ice			Effect_PistolSnow		imp_bullet_mud		15
		sand		Effect_PistolSand		IMP_BULLET_SAND		15
		quicksand	Effect_PistolSand		IMP_BULLET_SAND		15
		stone		Effect_PistolStone		IMP_BULLET_ROCK		15
		wood		Effect_PistolWood		IMP_BULLET_WOOD		5
		metal		Effect_PistolMetal		IMP_BULLET_METAL	15
		glass		Effect_PistolGlass		imp_glass			5
		cloth		Effect_PistolDirt		IMP_BULLET_CLOTH	3
		foliage		Effect_PistolFoliage	IMP_BULLET_FOLIAGE	3
		hmetal		Effect_PistolMetal		IMP_BULLET_ARMOR	15
		flesh		Effect_PistolBody		IMP_BULLET_FLESH	3
		player		Effect_PistolBody		IMP_BULLET_PLAYER	10
		zip			none					WSH_BULLET_BY		10
	end
end

ammo AMMO_M203_40MM_NADE
	bullet_mass 2000
	frndlyTrcrID 1874   
	max_age 40
	arm_age .1      
	velocity 95 
	recoil 45
	error 0
	drag  1
    ai_launch		GS_M203_GLAUNCH 
	Mf_Light 100
	scorch_id 2
	scar_type 2

	impact_damage 410

	kztype rounds_kz_C4
	kz_minradius 4.0
	kz_maxradius 10.0
	kz_damage 200

    kz_physics 1		


	light_impact   8.0  255 192 96  0.25

	flag LAWR
	flag	IgnorFoilage
	flag forcetracer

    impact_AI_damage 7	
    kz_AI_damage    100 

	effects_table
		move	   none		    none			0
		obj        Effect_GrenMetal		explo_ammo_med		200
		dirt       Effect_GrenGrnd		explo_dirt			200
		grass      Effect_GrenGrass		explo_ammo_med		200
		snow       Effect_GrenMetal		explo_dirt			200
		cement     Effect_GrenRoad		explo_ammo_med		200
		packeddirt Effect_GrenGrndSlp	explo_dirt			200
		water      effect_waterexp		explo_water_sm		200
		railroad   Effect_GrenMetal		explo_ammo_med		200
		mud        Effect_GrenGrnd		explo_ammo_med		200
		ice        Effect_GrenGrnd		explo_dirt			200
		quicksand	Effect_GrenQSand	explo_dirt			200
		sand		Effect_GrenSand		explo_dirt			200
		stone      Effect_GrenStone		explo_ammo_med		200
		wood       Effect_GrenWood		explo_ammo_med		200
		metal      Effect_GrenMetal		explo_ammo_med		200
		glass      Effect_GrenMetal		explo_ammo_med		200
		cloth      Effect_GrenObj		explo_ammo_med		200
		foliage    Effect_GrenFolio		explo_foliage		200
		hmetal     Effect_GrenMetal		explo_ammo_med		200
		flesh      Effect_GrenBody		explo_ammo_med		200
		player		Effect_GrenBody		explo_ammo_med		200
		zip			none				WSH_SHELL_BY		50
	end
end


ammo satchel
	bullet_mass	3
	frndlyTrcrID		1891   
	max_age		1     
	arm_age		0      
	velocity	6		
	error		1
	drag		1
	recoil		0

	scorch_id	2
	scar_type	2

	flag useownmove
	flag noage
	flag forcetracer
	flag priority

	light_impact   8.0  255 192 96  0.25

    impact_AI_damage 0
    kz_AI_damage    0 

	effects_table
		move		none				none				0
		obj			none		EXPLO_SATCHEL		200	
		dirt		none		IMP_SATCHEL_DRT		20	
		grass		none		IMP_SATCHEL_DRT		20	
		snow		none		IMP_SATCHEL_DRT		20	
		cement		none		IMP_SATCHEL_STN		20	
		packeddirt	none		IMP_SATCHEL_DRT		20	
		water		none		IMP_DEBSML_WATER	20	
		railroad	none		IMP_SATCHEL_MTL		20	
		mud			none		IMP_SATCHEL_MUD		20	
		ice			none		IMP_SATCHEL_STN		20	
		quicksand	none		IMP_SATCHEL_MUD		20	
		sand		none		IMP_SATCHEL_DRT 	20	
		stone		none		IMP_SATCHEL_STN		20	
		wood		none		IMP_SATCHEL_WD		20	
		metal		none		IMP_SATCHEL_MTL		20	
		glass		none		IMP_SATCHEL_STN		20	
		cloth		none		IMP_SATCHEL_CNV		20	
		foliage		none		IMP_GREN_FOLIAGE	20	
		hmetal		none		IMP_SATCHEL_MTL		20	
		flesh		none		IMP_SATCHEL_CNV		20	
		player		none		IMP_SATCHEL_CNV		20	
		zip			none		none				10	
	end
end

ammo satchelboom
	bullet_mass	3
	frndlyTrcrID		1891   
	max_age		1     
	arm_age		0      
	velocity	6		
	error		1
	drag		1
	recoil		0

	scorch_id	2
	scar_type	2

	flag instantkillzone

	kztype rounds_kz_Standard
	kz_minradius 1.0	
	kz_maxradius 8.0	
	kz_damage 2000		
	impact_damage 0		
    kz_physics 1		

	light_impact   8.0  255 192 96  0.25

    impact_AI_damage 0	
    kz_AI_damage    667 

	effects_table
		move		none				none				0
		obj			Effect_SATCHEL		EXPLO_SATCHEL		200	
		dirt		Effect_SATCHEL		none		20	
		grass		Effect_SATCHEL		none		20	
		snow		Effect_SATCHEL		none		20	
		cement		Effect_SATCHEL		none		20	
		packeddirt	Effect_SATCHEL		none 		20	
		water		Effect_SmlSplash	IMP_DEBSML_WATER	20	
		railroad	Effect_SATCHEL		none		20	
		mud			Effect_SATCHEL		none		20	
		ice			Effect_SATCHEL		none		20	
		quicksand	Effect_SATCHEL		none		20	
		sand		Effect_SATCHEL		none 		20	
		stone		Effect_SATCHEL		none		20	
		wood		Effect_SATCHEL		none		20	
		metal		Effect_SATCHEL		none		20	
		glass		Effect_SATCHEL		none		20	
		cloth		Effect_SATCHEL		none		20	
		foliage		Effect_SATCHEL		IMP_GREN_FOLIAGE	20	
		hmetal		Effect_SATCHEL		none		20	
		flesh		Effect_SATCHEL		none		20	
		player		Effect_SATCHEL		none		20	
		zip			none				none				10	
	end
end


ammo claymore
	bullet_mass	3
	frndlyTrcrID		1895   
	foeTrcrID			1895   
	max_age		1     
	arm_age		0      
	velocity	2		
	error		0
	drag		1
	recoil		0

	scorch_id	2
	scar_type	2

	flag useownmove
	flag noage
	flag forcetracer
	flag priority

	kztype rounds_kz_C4  
	kz_damage 105
	kz_minradius 5
	kz_maxradius 15
	kz_pieslice	 24		

	light_impact   8.0  255 192 96  0.25

    impact_AI_damage 0	
    kz_AI_damage    35 

	effects_table
		move		none				none				0
		obj			Effect_FragGrndDirt	EXPLO_CLAYMORE		200	
		dirt		Effect_FragGrndDirt	IMP_CLAYMORE_DT		20	
		grass		Effect_FragGrndDirt	IMP_CLAYMORE_DT		20	
		snow		Effect_FragGrndDirt	IMP_CLAYMORE_DT		20	
		cement		Effect_FragGrndDirt	IMP_CLAYMORE_ST		20	
		packeddirt	Effect_FragGrndDirt	IMP_CLAYMORE_DT		20	
		water		Effect_SmlSplash	IMP_DEBSML_WATER	20	
		railroad	Effect_FragGrndDirt	IMP_CLAYMORE_MT		20	
		mud			Effect_FragGrndDirt	IMP_CLAYMORE_DT		20	
		ice			Effect_FragGrndDirt	IMP_CLAYMORE_DT		20	
		quicksand	Effect_FragGrndDirt	IMP_CLAYMORE_DT		20	
		sand		Effect_FragGrndDirt	IMP_CLAYMORE_DT		20	
		stone		Effect_FragGrndDirt	IMP_CLAYMORE_ST		20	
		wood		Effect_FragGrndDirt	IMP_CLAYMORE_WD		20	
		metal		Effect_FragGrndDirt	IMP_CLAYMORE_MT		20	
		glass		Effect_FragGrndDirt	IMP_GLASS			20	
		cloth		Effect_FragGrndDirt	IMP_CLAYMORE_CV		20	
		foliage		Effect_FragGrndDirt	IMP_GREN_FOLIAGE	20	
		hmetal		Effect_FragGrndDirt	IMP_CLAYMORE_MT		20	
		flesh		Effect_FragGrndDirt	IMP_GREN_FLESH		20	
		player		Effect_FragGrndDirt	IMP_GREN_FLESH		20	
		zip			none				none				10	
	end
end



ammo claymorekillzone
	bullet_mass	3
	max_age		1     
	arm_age		0      
	velocity	2		
	error		0
	drag		1
	recoil		0

	scorch_id	2
	scar_type	2

	flag instantkillzone

	kztype rounds_kz_C4  
	kz_damage 105
	kz_minradius 5
	kz_maxradius 15
	kz_pieslice	 24		

	light_impact   8.0  255 192 96  0.25

    impact_AI_damage 0	
    kz_AI_damage    35 

	effects_table
		obj			Effect_FragGrndDirt		EXPLO_CLAYMORE		200	
		dirt       Effect_SGvDirt			IMP_BULLET_DIRT		15
		grass      Effect_SGvGrass			imp_bullet_grass	15
		snow       Effect_SGvSnow			IMP_BULLET_DIRT		1
		cement     Effect_SGvStone			IMP_12GAGE_ROCK		15
		packeddirt Effect_SGvDirt			IMP_BULLET_DIRT		15
		water      Effect_SGvWater			IMP_12GAGE_WATER	5
		railroad   Effect_SGvMetal			IMP_BULLET_ARMOR	15
		mud        Effect_SGvDirt			imp_bullet_mud		15
		ice        Effect_SGvSnow			imp_bullet_mud		15
		sand       Effect_SGvSand			IMP_BULLET_SAND		15
		quicksand  Effect_SGvSand			IMP_BULLET_SAND		15
		stone      Effect_SGvStone			IMP_12GAGE_ROCK		15
		wood       Effect_SGvDirt			IMP_BULLET_WOOD		5
		metal      Effect_SGvMetal			IMP_BULLET_ARMOR	15
		glass      Effect_SGvGlass			imp_glass			5
		cloth      Effect_SGvDirt			IMP_BULLET_CLOTH	3
		foliage    Effect_SGvGrass			IMP_BULLET_FOLIAGE	3
		hmetal     Effect_SGvMetal			IMP_BULLET_ARMOR	15
		flesh      Effect_SGvBody			IMP_BULLET_FLESH	3
		player	   Effect_SGvBody			IMP_BULLET_FLESH	10
		zip		   Effect_SGvBody			wsh_shell_by		10
	end
end

ammo claymoreshrapnel
	bullet_mass 1
	max_age .5 
	velocity 388
	error 0
	drag  1
	scorch_id 1
	scar_type 1
	recoil		0

	impact_damage 35

	flag claymore

	spread_count	16
	kz_pieslice	 48		

    impact_AI_damage 12	
    kz_AI_damage    0 

	effects_table
		dirt       Effect_SGvDirt			SHRAPNEL_DIRT		15
		grass      Effect_SGvGrass			SHRAPNEL_DIRT		15
		snow       Effect_SGvSnow			SHRAPNEL_DIRT		1
		cement     Effect_SGvStone			IMP_12GAGE_ROCK		15
		packeddirt Effect_SGvDirt			SHRAPNEL_DIRT		15
		water      Effect_SGvWater			IMP_12GAGE_WATER	5
		railroad   Effect_SGvMetal			IMP_BULLET_ARMOR	15
		mud        Effect_SGvDirt			SHRAPNEL_DIRT		15
		ice        Effect_SGvSnow			SHRAPNEL_DIRT		15
		sand       Effect_SGvSand			IMP_BULLET_SAND		15
		quicksand  Effect_SGvSand			IMP_BULLET_SAND		15
		stone      Effect_SGvStone			IMP_12GAGE_ROCK		15
		wood       Effect_SGvDirt			IMP_BULLET_WOOD		5
		metal      Effect_SGvMetal			IMP_BULLET_ARMOR	15
		glass      Effect_SGvGlass			imp_glass			5
		cloth      Effect_SGvDirt			IMP_12G_CLOTH		3
		foliage    Effect_SGvGrass			IMP_BULLET_FOLIAGE	3
		hmetal     Effect_SGvMetal			IMP_BULLET_ARMOR	15
		flesh      Effect_SGvBody			IMP_BULLET_FLESH	3
		player	   Effect_SGvBody			IMP_BULLET_FLESH	10
		zip		   Effect_SGvBody			wsh_shell_by		10
	end
end

ammo detonator
	bullet_mass	0

	max_age		0     
	arm_age		0      
	velocity	0		
	error		0
	drag		1
	recoil		0

	flag Detonatesatchels

    impact_AI_damage 0	
    kz_AI_damage    0 
	
	effects_table
		move		none	none	0
		obj			none	none	200	
		dirt		none	none	20	
		grass		none	none	20	
		snow		none	none	20	
		cement		none	none	20	
		packeddirt	none	none	20	
		water		none	none	20	
		railroad	none	none	20	
		mud			none	none	20	
		ice			none	none	20	
		quicksand	none	none	20	
		sand		none	none	20	
		stone		none	none	20	
		wood		none	none	20	
		metal		none	none	20	
		glass		none	none	20	
		cloth		none	none	20	
		foliage		none	none	20	
		hmetal		none	none	20	
		flesh		none	none	20	
		player		none	none	20	
		zip			none	none	10	
	end
end



ammo SMALLLANDMINE 
	bullet_mass	3
	max_age		1     
	arm_age		0      
	velocity	2		
	error		0
	drag		1

	scorch_id	2
	scar_type	2

    ai_launch		EXPLO_MINE_SM 
	ai_Launcheffect Effect_FragGrndDirt

	flag instantkillzone

	kztype rounds_kz_C4  
	kz_damage 105
	kz_minradius 2
	kz_maxradius 5

	light_impact   8.0  255 192 96  0.25

    impact_AI_damage 0	
    kz_AI_damage    35 

	effects_table
		obj			Effect_FragGrndDirt		EXPLO_MINE_SM		200	
		dirt       Effect_SGvDirt			IMP_BULLET_DIRT		15
		grass      Effect_SGvGrass			imp_bullet_grass	15
		snow       Effect_SGvSnow			IMP_BULLET_DIRT		1
		cement     Effect_SGvStone			IMP_12GAGE_ROCK		15
		packeddirt Effect_SGvDirt			IMP_BULLET_DIRT		15
		water      Effect_SGvWater			IMP_12GAGE_WATER	5
		railroad   Effect_SGvMetal			IMP_BULLET_ARMOR	15
		mud        Effect_SGvDirt			imp_bullet_mud		15
		ice        Effect_SGvSnow			imp_bullet_mud		15
		sand       Effect_SGvSand			IMP_BULLET_SAND		15
		quicksand  Effect_SGvSand			IMP_BULLET_SAND		15
		stone      Effect_SGvStone			IMP_12GAGE_ROCK		15
		wood       Effect_SGvDirt			IMP_BULLET_WOOD		5
		metal      Effect_SGvMetal			IMP_BULLET_ARMOR	15
		glass      Effect_SGvGlass			imp_glass			5
		cloth      Effect_SGvDirt			IMP_BULLET_CLOTH	3
		foliage    Effect_SGvGrass			IMP_BULLET_FOLIAGE	3
		hmetal     Effect_SGvMetal			IMP_BULLET_ARMOR	15
		flesh      Effect_SGvBody			IMP_BULLET_FLESH	3
		player	   Effect_SGvBody			IMP_BULLET_FLESH	10
		zip		   Effect_SGvBody			wsh_shell_by		10
	end
end


ammo LARGELANDMINE
	bullet_mass	3
	max_age		1     
	arm_age		0      
	velocity	2		
	error		0
	drag		1

	scorch_id	2
	scar_type	2

    ai_launch		EXPLO_MINE_LG 
	ai_Launcheffect Effect_FragGrndDirt


	flag instantkillzone

	kztype rounds_kz_C4  
	kz_damage 500
	kz_minradius 4
	kz_maxradius 8

	light_impact   8.0  255 192 96  0.25

    impact_AI_damage 0	
    kz_AI_damage    167 

	effects_table
		obj			Effect_FragGrndDirt		EXPLO_MINE_LG		200	
		dirt       Effect_SGvDirt			IMP_BULLET_DIRT		15
		grass      Effect_SGvGrass			imp_bullet_grass	15
		snow       Effect_SGvSnow			IMP_BULLET_DIRT		1
		cement     Effect_SGvStone			IMP_12GAGE_ROCK		15
		packeddirt Effect_SGvDirt			IMP_BULLET_DIRT		15
		water      Effect_SGvWater			IMP_12GAGE_WATER	5
		railroad   Effect_SGvMetal			IMP_BULLET_ARMOR	15
		mud        Effect_SGvDirt			imp_bullet_mud		15
		ice        Effect_SGvSnow			imp_bullet_mud		15
		sand       Effect_SGvSand			IMP_BULLET_SAND		15
		quicksand  Effect_SGvSand			IMP_BULLET_SAND		15
		stone      Effect_SGvStone			IMP_12GAGE_ROCK		15
		wood       Effect_SGvDirt			IMP_BULLET_WOOD		5
		metal      Effect_SGvMetal			IMP_BULLET_ARMOR	15
		glass      Effect_SGvGlass			imp_glass			5
		cloth      Effect_SGvDirt			IMP_BULLET_CLOTH	3
		foliage    Effect_SGvGrass			IMP_BULLET_FOLIAGE	3
		hmetal     Effect_SGvMetal			IMP_BULLET_ARMOR	15
		flesh      Effect_SGvBody			IMP_BULLET_FLESH	3
		player	   Effect_SGvBody			IMP_BULLET_FLESH	10
		zip		   Effect_SGvBody			wsh_shell_by		10
	end
end


ammo grenadehe
	bullet_mass	3
	frndlyTrcrID		1883   
	max_age		4     
	arm_age		0      
	velocity	30		
	error		1
	drag		1
	recoil		0

	scorch_id	2
	scar_type	2

	flag	useownmove
	flag	IgnorFoilage
	flag	forcetracer
	flag	priority

	kztype rounds_kz_C4
	kz_minradius 6.0	
	kz_maxradius 12.0	
	kz_damage 205			
    kz_physics 1		


    impact_AI_damage 0	
    kz_AI_damage    105 

	effects_table
		move		none				none				0
		obj			Effect_FragGrndDirt	explo_ammo_med		80	
		dirt		Effect_FragGrndDirt	IMP_GREN_DIRT		20	
		grass		Effect_FragGrndDirt	IMP_GREN_DIRT		20	
		snow		Effect_FragGrndDirt	IMP_GREN_DIRT		20	
		cement		Effect_FragGrndDirt	IMP_GREN_STON		20	
		packeddirt	Effect_FragGrndDirt	IMP_GREN_DIRT		20	
		water		Effect_SmlSplash	IMP_DEBSML_WATER	20	
		railroad	Effect_FragGrndDirt	IMP_GREN_METAL		20	
		mud			Effect_FragGrndDirt	IMP_GREN_DIRT		20	
		ice			Effect_FragGrndDirt	IMP_GREN_DIRT		20	
		quicksand	Effect_FragGrndDirt	IMP_GREN_DIRT		20	
		sand		Effect_FragGrndDirt	IMP_GREN_DIRT		20	
		stone		Effect_FragGrndDirt	IMP_GREN_STON		20	
		wood		Effect_FragGrndDirt	IMP_GREN_WOOD		20	
		metal		Effect_FragGrndDirt	IMP_GREN_METAL		20	
		glass		Effect_FragGrndDirt	IMP_GLASS			20	
		cloth		Effect_FragGrndDirt	IMP_GREN_CANV		20	
		foliage		Effect_FragGrndDirt	IMP_GREN_FOLIAGE	20	
		hmetal		Effect_FragGrndDirt	IMP_GREN_METAL		20	
		flesh		Effect_FragGrndDirt	IMP_GREN_FLESH		20	
		player		Effect_FragGrndDirt	IMP_GREN_FLESH		20	
		zip			none				none				10	
	end
end

ammo grenadesm
	bullet_mass	3
	frndlyTrcrID		1875   
	max_age		30     
	arm_age		5      
	velocity	30		
	error		1
	drag		1
	recoil		0

	scorch_id 2
	scar_type 2

	flag useownmove
	flag	IgnorFoilage
	flag forcetracer
	flag priority



    impact_AI_damage 0	
    kz_AI_damage    0 
	effects_table
		move	   Effect_SmokeToss	none				0
		obj        none		EXPLO_SMOK_GREN		80	
		dirt       none		IMP_GREN_DIRT		20	
		grass      none		IMP_GREN_DIRT		20	
		snow       none		IMP_GREN_DIRT		20	
		cement     none		IMP_GREN_STON		20	
		packeddirt none		IMP_GREN_DIRT		20	
		water      Effect_SmlSplash		IMP_DEBSML_WATER	20	
		railroad   none		IMP_GREN_METAL		20	
		mud        none		IMP_GREN_DIRT		20	
		ice        none		IMP_GREN_DIRT		20	
		quicksand	none	IMP_GREN_DIRT		20	
		sand		none	IMP_GREN_DIRT		20	
		stone      none		IMP_GREN_STON		20	
		wood       none		IMP_GREN_WOOD		20	
		metal      none		IMP_GREN_METAL		20	
		glass      none		IMP_GLASS			20	
		cloth      none		IMP_GREN_CANV		20	
		foliage    none		IMP_GREN_FOLIAGE	20	
		hmetal     none		IMP_GREN_METAL		20	
		flesh      none		IMP_GREN_FLESH		20	
		player		none	IMP_GREN_FLESH		20	
		zip			none	none				10	
	end
end

ammo grenadefb
	bullet_mass	3
	frndlyTrcrID		1875   
	max_age		4      
	arm_age		0      
	velocity	30	
	error		1
	drag		1
	recoil		0

	scorch_id 2
	scar_type 2

	flag useownmove
	flag	IgnorFoilage
	flag forcetracer
	flag priority

	kztype rounds_kz_C4
	kz_minradius 20.0
	kz_maxradius 20.0
	kz_damage 0
    kz_physics 3		
    secondary_anim  2	


    impact_AI_damage 0	
    kz_AI_damage    0 

	effects_table
		move		Effect_FlashBangToss	none				0
		obj			Effect_FlashBang		EXPLO_FLASHBANG		80	
		dirt		Effect_FlashBangDirt	IMP_GREN_DIRT		20	
		grass		Effect_FlashBang		IMP_GREN_DIRT		20	
		snow		Effect_FlashBang		IMP_GREN_DIRT		20	
		cement		Effect_FlashBangDirt	IMP_GREN_STON		20	
		packeddirt	Effect_FlashBangDirt	IMP_GREN_DIRT		20	
		water		Effect_SmlSplash			IMP_DEBSML_WATER	20	
		railroad	Effect_FlashBang		IMP_GREN_METAL		20	
		mud			Effect_FlashBangDirt	IMP_GREN_DIRT		20	
		ice			Effect_FlashBang		IMP_GREN_DIRT		20	
		quicksand	Effect_FlashBangDirt	IMP_GREN_DIRT		20	
		sand		Effect_FlashBangDirt	IMP_GREN_DIRT		20	
		stone		Effect_FlashBangDirt	IMP_GREN_STON		20	
		wood		Effect_FlashBang		IMP_GREN_WOOD		20	
		metal		Effect_FlashBang		IMP_GREN_METAL		20	
		glass		Effect_FlashBang		IMP_GLASS			20	
		cloth		Effect_FlashBang		IMP_GREN_CANV		20	
		foliage		Effect_FlashBangDirt	IMP_GREN_FOLIAGE	20	
		hmetal		Effect_FlashBang		IMP_GREN_METAL		20	
		flesh		Effect_FlashBang		IMP_GREN_FLESH		20	
		player		Effect_FlashBang		IMP_GREN_FLESH		20	
		zip			none					none				10	
	end
end

ammo grenadecs
	bullet_mass	3
	frndlyTrcrID		1875   
	max_age		5     
	arm_age		0      
	velocity	30		
	error		1
	drag		1
	recoil		0

	scorch_id 2
	scar_type 2

	flag useownmove
	flag	IgnorFoilage
	flag forcetracer
	flag priority

	kztype rounds_kz_C4
	kz_minradius 1.0
	kz_maxradius 6.0
	kz_damage 32
	impact_damage 128




    impact_AI_damage 0	
    kz_AI_damage    10 

	effects_table
		move	   Effect_ChemGasToss	none				0
		obj        Effect_ChemGas		EXPLO_SMOK_GREN		80	
		dirt       Effect_ChemGas		IMP_GREN_DIRT		20	
		grass      Effect_ChemGas		IMP_GREN_DIRT		20	
		snow       Effect_ChemGas		IMP_GREN_DIRT		20	
		cement     Effect_ChemGas		IMP_GREN_STON		20	
		packeddirt Effect_ChemGas		IMP_GREN_DIRT		20	
		water      Effect_SmlSplash		IMP_DEBSML_WATER	20	
		railroad   Effect_ChemGas		IMP_GREN_METAL		20	
		mud        Effect_ChemGas		IMP_GREN_DIRT		20	
		ice        Effect_ChemGas		IMP_GREN_DIRT		20	
		quicksand	Effect_ChemGas		IMP_GREN_DIRT		20	
		sand		Effect_ChemGas		IMP_GREN_DIRT		20	
		stone      Effect_ChemGas		IMP_GREN_STON		20	
		wood       Effect_ChemGas		IMP_GREN_WOOD		20	
		metal      Effect_ChemGas		IMP_GREN_METAL		20	
		glass      Effect_ChemGas		IMP_GLASS			20	
		cloth      Effect_ChemGas		IMP_GREN_CANV		20	
		foliage    Effect_ChemGas		IMP_GREN_FOLIAGE	20	
		hmetal     Effect_ChemGas		IMP_GREN_METAL		20	
		flesh      Effect_ChemGas		IMP_GREN_FLESH		20	
		player		Effect_ChemGas		IMP_GREN_FLESH		20	
		zip			none				none				10	
	end
end

ammo medpack
	bullet_mass 1
	max_age 1     
	velocity 1		
	error 0
	drag  1
	recoil		0

	impact_damage 0
    
	flag instantkillzone
	kztype rounds_kz_Medic
	kz_damage 0
	kz_minradius 2
	kz_maxradius 2

    impact_AI_damage 0	
    kz_AI_damage    0 

	effects_table
		move		none				none		0
		obj			none				none		50
		dirt		none				none		50
		grass		none				none		50
		snow		none				none		50
		cement		none				none		50
		packeddirt	none				none		50
		water		none				none		50
		railroad	none				none		50
		mud			none				none		50
		ice			none				none		50
		quicksand	none				none		50
		sand		none				none		50
		stone		none				none		50
		wood		none				none		50
		metal		none				none		50
		glass		none				none		50
		cloth		none				none		50
		foliage		none				none		50
		hmetal		none			    none		50
		flesh		none				none		50
		player		none				none		50
		zip			none				none		50
	end
end

ammo MK19nade
	bullet_mass 3
	frndlyTrcrID 1874   
	max_age 7    
	arm_age .05    
	velocity 241
	recoil 15
	error 1
	drag  1
    ai_launch		GS_M203_GLAUNCH 
	Mf_Light 100
	scorch_id 2
	scar_type 2

	impact_damage 30

	kztype rounds_kz_C4
	kz_minradius 2.0		
	kz_maxradius 10.0		
	kz_damage 300			

    kz_physics 1		


	
	light_impact   8.0  255 192 96  0.25

	flag LAWR
	flag forcetracer
	

    impact_AI_damage 10	
    kz_AI_damage    100 

	effects_table
		move	   none				    none			0
		obj        Effect_GrenObj		explo_ammo_med		200
		dirt       Effect_GrenGrnd		explo_dirt			200
		grass      Effect_GrenGrass		explo_ammo_med		200
		snow       Effect_SmlSnowExp	explo_dirt			200
		cement     Effect_GrenRoad		explo_ammo_med		200
		packeddirt Effect_GrenGrnd		explo_dirt			200
		water      effect_waterexp		explo_water_sm		200
		railroad   Effect_GrenMetal		explo_ammo_med		200
		mud        Effect_GrenGrnd		explo_ammo_med		200
		ice        Effect_SmlSnowExp	explo_dirt			200
		quicksand	Effect_GrenQSand	explo_dirt			200
		sand		Effect_GrenSand		explo_dirt			200
		stone      Effect_GrenStone		explo_ammo_med		200
		wood       Effect_GrenWood		explo_ammo_med		200
		metal      Effect_GrenMetal		explo_ammo_med		200
		glass      Effect_GrenObj		explo_ammo_med		200
		cloth      Effect_GrenObj		explo_ammo_med		200
		foliage    Effect_GrenFolio		explo_foliage		200
		hmetal     Effect_GrenMetal		explo_ammo_med		200
		flesh      Effect_GrenBody		explo_ammo_med		200
		player		Effect_GrenBody		explo_ammo_med		200
		zip			none				WSH_SHELL_BY		50
	end
end

ammo Rclsrnd
	bullet_mass 3
	frndlyTrcrID 1874   
	max_age 4    
	arm_age .05    
	velocity 250
	recoil 5
	error 1
	drag  1
    ai_launch		GS_EMCANNON 
	Mf_Light 100
	scorch_id 2
	scar_type 2

	impact_damage 200

	kztype rounds_kz_C4
	kz_minradius 3.0	
	kz_maxradius 7.0	
	kz_damage 500		

    kz_physics 1		


	
	light_impact   8.0  255 192 96  0.25

	flag LAWR
	

    impact_AI_damage 67	
    kz_AI_damage    167 

	effects_table
		move	   none				    none			0
		obj        Effect_GrenObj		explo_ammo_med		200
		dirt       Effect_GrenGrnd		explo_dirt			200
		grass      Effect_GrenGrass		explo_ammo_med		200
		snow       Effect_SmlSnowExp	explo_dirt			200
		cement     Effect_GrenRoad		explo_ammo_med		200
		packeddirt Effect_GrenGrnd		explo_dirt			200
		water      effect_waterexp		explo_water_sm		200
		railroad   Effect_GrenMetal		explo_ammo_med		200
		mud        Effect_GrenGrnd		explo_ammo_med		200
		ice        Effect_SmlSnowExp	explo_dirt			200
		quicksand	Effect_GrenQSand	explo_dirt			200
		sand		Effect_GrenSand		explo_dirt			200
		stone      Effect_GrenStone		explo_ammo_med		200
		wood       Effect_GrenWood		explo_ammo_med		200
		metal      Effect_GrenMetal		explo_ammo_med		200
		glass      Effect_GrenObj		explo_ammo_med		200
		cloth      Effect_GrenObj		explo_ammo_med		200
		foliage    Effect_GrenFolio		explo_foliage		200
		hmetal     Effect_GrenMetal		explo_ammo_med		200
		flesh      Effect_GrenBody		explo_ammo_med		200
		player		Effect_GrenBody		explo_ammo_med		200
		zip			none				WSH_SHELL_BY		50
	end
end


ammo minirnds
	bullet_mass 147
	max_age 5
	velocity 853
	error 3
	drag  1
	recoil 3
	scar_type 1
	frndlyTrcrID 4405
	foeTrcrID	 4406
	Mf_Light 100
    flag muzzle1  
    
	bullet_radius .4	

	impact_damage 200

	kztype rounds_kz_C4
	kz_damage 0		
	kz_minradius .75	
	kz_maxradius .75	

    impact_AI_damage 35	
    kz_AI_damage    0 

	effects_table
		move		none					none				0
		obj			Effect_PistolMetal		IMP_BULLET_DIRT		15
		dirt		Effect_PistolDirt		IMP_BULLET_DIRT		15
		grass		Effect_PistolGrass		imp_bullet_grass	15
		snow		Effect_PistolSnow		IMP_BULLET_DIRT		1
		cement		Effect_PistolStone		IMP_BULLET_ROCK		15
		packeddirt	Effect_PistolDirt		imp_20mm_dirt		15
		water		Effect_PistolWater		IMP_BULLET_WATER	5
		railroad	Effect_PistolMetal		IMP_BULLET_METAL	15
		mud			Effect_PistolDirt		imp_bullet_mud		15
		ice			Effect_PistolSnow		imp_bullet_mud		15
		sand		Effect_PistolSand		IMP_BULLET_SAND		15
		quicksand	Effect_PistolSand		IMP_BULLET_SAND		15
		stone		Effect_PistolStone		IMP_BULLET_ROCK		15
		wood		Effect_PistolWood		IMP_BULLET_WOOD		5
		metal		Effect_PistolMetal		IMP_BULLET_METAL	15
		glass		Effect_PistolGlass		imp_glass			5
		cloth		Effect_PistolDirt		IMP_BULLET_CLOTH		3
		foliage		Effect_PistolFoliage	IMP_BULLET_FOLIAGE	3
		hmetal		Effect_PistolMetal		IMP_BULLET_ARMOR	15
		flesh		Effect_PistolBody		IMP_BULLET_FLESH	3
		player		Effect_PistolBody		IMP_BULLET_PLAYER	10
		zip			none					WSH_BULLET_BY2		10
	end
end


ammo wkminirnds
	bullet_mass 1
	max_age 1.5 
	velocity 862
	error 3
	drag  1
	recoil 10
	scar_type 1
	frndlyTrcrID 4405
	foeTrcrID	 4406
	Mf_Light 100
    flag muzzle1  
    
	bullet_radius .4	

	impact_damage 300

	kztype rounds_kz_C4
	kz_damage 0		
	kz_minradius .75	
	kz_maxradius .75	

    impact_AI_damage 5	
    kz_AI_damage    0 

	effects_table
		move       none						none				0
		obj        Effect_FX50CalObj		IMP_BULLET_DIRT		15
		dirt       Effect_FX50CalDirt		IMP_BULLET_DIRT		15
		grass      Effect_FX50CalGrass		imp_bullet_grass	15
		snow       Effect_FX50CalDirt		IMP_BULLET_DIRT		1
		cement     Effect_FX50CalStone		IMP_BULLET_ROCK		15
		packeddirt Effect_FX50CalDirt		imp_20mm_dirt		15
		water      Effect_WatersplshMed		IMP_BULLET_WATER	5
		railroad   Effect_FX50CalMetal		IMP_BULLET_METAL	15
		mud        Effect_FX50CalDirt		imp_bullet_mud		15
		ice        Effect_PistolSnow		imp_bullet_mud		15
		sand       Effect_FX50CalSand		IMP_BULLET_SAND		15
		quicksand  Effect_FX50CalSand		IMP_BULLET_SAND		15
		stone      Effect_FX50CalStone		IMP_BULLET_ROCK		15
		wood       Effect_FX50CalWood		IMP_BULLET_WOOD		5
		metal      Effect_FX50CalMetal		IMP_BULLET_METAL	15
		glass      Effect_FX50CalGlass		imp_glass			5
		cloth      Effect_FX50CalObj		IMP_BULLET_CLOTH	3
		foliage    Effect_FX50CalWoodF		IMP_BULLET_FOLIAGE	3
		hmetal     Effect_FX50CalMetal		IMP_BULLET_ARMOR	15
		flesh      Effect_FX50CalBody		IMP_BULLET_FLESH	3
		player		Effect_FX50CalBody		imp_bullet_flesh	10
		zip			none					wsh_bullet_by		10
	end
end


ammo minirnds_zerodamage
	bullet_mass 1
	max_age 1.5 
	velocity 180
	error 3
	drag  1
	recoil 10
	scar_type 1
	frndlyTrcrID 4405
	foeTrcrID	 4406
	Mf_Light 100
    flag muzzle1  
	bullet_radius .4	

	impact_damage 0

	kztype rounds_kz_C4
	kz_damage 0		
	kz_minradius .75	
	kz_maxradius .75	

    impact_AI_damage 0
    kz_AI_damage    0 

	effects_table
		move       none						none				0
		obj        Effect_FX50CalObj		IMP_BULLET_DIRT		15
		dirt       Effect_FX50CalDirt		IMP_BULLET_DIRT		15
		grass      Effect_FX50CalGrass		imp_bullet_grass	15
		snow       Effect_FX50CalDirt		IMP_BULLET_DIRT		1
		cement     Effect_FX50CalStone		IMP_BULLET_ROCK		15
		packeddirt Effect_FX50CalDirt		imp_20mm_dirt		15
		water      Effect_WatersplshMed		IMP_BULLET_WATER	5
		railroad   Effect_FX50CalMetal		IMP_BULLET_METAL	15
		mud        Effect_FX50CalDirt		imp_bullet_mud		15
		ice        Effect_PistolSnow		imp_bullet_mud		15
		sand       Effect_FX50CalSand		IMP_BULLET_SAND		15
		quicksand  Effect_FX50CalSand		IMP_BULLET_SAND		15
		stone      Effect_FX50CalStone		IMP_BULLET_ROCK		15
		wood       Effect_FX50CalWood		IMP_BULLET_WOOD		5
		metal      Effect_FX50CalMetal		IMP_BULLET_METAL	15
		glass      Effect_FX50CalGlass		imp_glass			5
		cloth      Effect_FX50CalObj		IMP_BULLET_CLOTH	3
		foliage    Effect_FX50CalWoodF		IMP_BULLET_FOLIAGE	3
		hmetal     Effect_FX50CalMetal		IMP_BULLET_ARMOR	15
		flesh      Effect_FX50CalBody		IMP_BULLET_FLESH	3
		player		Effect_FX50CalBody		imp_bullet_flesh	10
		zip			none					wsh_bullet_by		10
	end
end

ammo 50CAL
	bullet_mass 200
	max_age 3.5
	velocity 930
	flag	IgnorFoilage
	error 3
	drag  1
	recoil	10
	scar_type 1
	frndlyTrcrID 4405
	foeTrcrID	 4406
    ai_launch		GS_AI50CAL 
    flag muzzle1  
	bullet_radius  0.5
	Mf_Light 100
	kztype rounds_kz_C4  
	kz_damage 0
	kz_minradius 2.5
	kz_maxradius 2.5

	impact_damage 300

    impact_AI_damage 20
    kz_AI_damage    0 

	effects_table
		move       none					 none          0
		obj        Effect_FX50CalObj	IMP_30MM_DIRT   15
		dirt       Effect_FX50CalDirt	IMP_30MM_DIRT   15
		grass      Effect_FX50CalGrass	imp_bullet_grass  15
		snow       Effect_FX50CalDirt	IMP_30MM_DIRT   1
		cement     Effect_FX50CalStone	IMP_30MM_DIRT   15
		packeddirt Effect_FX50CalDirt	IMP_30MM_DIRT   15
		water      Effect_WatersplshMed	imp_bullet_water  5
		railroad   Effect_FX50CalMetal	IMP_20MM_METAL	  15
		mud        Effect_FX50CalDirt	imp_bullet_mud    15
		ice        Effect_PistolSnow	imp_bullet_mud    15
		sand       Effect_FX50CalSand	imp_bullet_sand   15
		quicksand  Effect_FX50CalSand	imp_bullet_sand   15
		stone      Effect_FX50CalStone	imp_bullet_rock  15
		wood       Effect_FX50CalWood	imp_bullet_wood   5
		metal      Effect_FX50CalMetal	IMP_20MM_METAL	  15
		glass      Effect_FX50CalGlass	imp_glass         5
		cloth      Effect_FX50CalObj	IMP_BULLET_CLOTH 3
		foliage    Effect_FX50CalWoodF	IMP_20MM_FOLIAGE   3
		hmetal     Effect_FX50CalMetal	IMP_30MM_ARMOR	  15
		flesh      Effect_FX50CalBody	imp_bullet_flesh  3
		player	   Effect_FX50CalBody	IMP_BULLET_PLAYER	10
		zip		   none					wsh_shell_by	20
	end
end

ammo kz_OrganicBlast
	bullet_mass	3
	max_age		1     
	arm_age		0      
	velocity	6		
	error		1
	drag		1
	recoil		0


	flag instantkillzone
	flag NoMItems
	flag NoDItems	

	kztype rounds_kz_RadiusBlast
	kz_minradius 4.0	
	kz_maxradius 4.0	
	kz_damage 1000		
	impact_damage 0		
    kz_physics 1		

    impact_AI_damage 0	
    kz_AI_damage    1000 

	effects_table
		move		none		none				0
		obj			none		none		200	
		dirt		none		none		20	
		grass		none		none		20	
		snow		none		none		20	
		cement		none		none		20	
		packeddirt	none		none 		20	
		water		none		none		20	
		railroad	none		none		20	
		mud			none		none		20	
		ice			none		none		20	
		quicksand	none		none		20	
		sand		none		none 		20	
		stone		none		none		20	
		wood		none		none		20	
		metal		none		none		20	
		glass		none		none		20	
		cloth		none		none		20	
		foliage		none		none		20	
		hmetal		none		none		20	
		flesh		none		none		20	
		player		none		none		20	
		zip			none		none		10	
	end
end

ammo kz_MItemBlast
	bullet_mass	3
	max_age		1     
	arm_age		0      
	velocity	6		
	error		1
	drag		1
	recoil		0

	scorch_id	2
	scar_type	2

	flag instantkillzone
	flag NoOItems
	flag NoDItems	

	kztype rounds_kz_Standard
	kz_minradius 4.0	
	kz_maxradius 4.0	
	kz_damage 2000		
	impact_damage 0		
    kz_physics 1		

    impact_AI_damage 0	
    kz_AI_damage    2000 

	effects_table
		move		none		none				0
		obj			none		none		200	
		dirt		none		none		20	
		grass		none		none		20	
		snow		none		none		20	
		cement		none		none		20	
		packeddirt	none		none 		20	
		water		none		none		20	
		railroad	none		none		20	
		mud			none		none		20	
		ice			none		none		20	
		quicksand	none		none		20	
		sand		none		none 		20	
		stone		none		none		20	
		wood		none		none		20	
		metal		none		none		20	
		glass		none		none		20	
		cloth		none		none		20	
		foliage		none		none		20	
		hmetal		none		none		20	
		flesh		none		none		20	
		player		none		none		20	
		zip			none		none		10	
	end
end

ammo kz_DebrisBlast
	bullet_mass	3
	max_age		1     
	arm_age		0      
	velocity	6		
	error		1
	drag		1
	recoil		0

	scorch_id	2
	scar_type	2

	flag instantkillzone
	flag NoMItems
	flag NoDItems	

	kztype rounds_kz_Standard
	kz_minradius 1.0	
	kz_maxradius 1.0	
	kz_damage 2000		
	impact_damage 0		
    kz_physics 1		

    impact_AI_damage 0	
    kz_AI_damage    2000 

	effects_table
		move		none		none				0
		obj			none		none		200	
		dirt		none		none		20	
		grass		none		none		20	
		snow		none		none		20	
		cement		none		none		20	
		packeddirt	none		none 		20	
		water		none		none		20	
		railroad	none		none		20	
		mud			none		none		20	
		ice			none		none		20	
		quicksand	none		none		20	
		sand		none		none 		20	
		stone		none		none		20	
		wood		none		none		20	
		metal		none		none		20	
		glass		none		none		20	
		cloth		none		none		20	
		foliage		none		none		20	
		hmetal		none		none		20	
		flesh		none		none		20	
		player		none		none		20	
		zip			none		none		10	
	end
end


ammo kz_M406HE
	bullet_mass	3
	max_age		1     
	arm_age		0      
	velocity	6		
	error		1
	drag		1
	recoil		0
	Mf_Light 100
	scorch_id	2
	scar_type	2

	flag instantkillzone	

	kztype rounds_kz_Standard
	kz_minradius 10.0	
	kz_maxradius 10.0	
	kz_damage 1000		
	impact_damage 0		
    kz_physics 1		

    impact_AI_damage 0	
    kz_AI_damage    1000 

	effects_table
		move		none		none		0
		obj			none		none		200	
		dirt		none		none		20	
		grass		none		none		20	
		snow		none		none		20	
		cement		none		none		20	
		packeddirt	none		none 		20	
		water		none		none		20	
		railroad	none		none		20	
		mud			none		none		20	
		ice			none		none		20	
		quicksand	none		none		20	
		sand		none		none 		20	
		stone		none		none		20	
		wood		none		none		20	
		metal		none		none		20	
		glass		none		none		20	
		cloth		none		none		20	
		foliage		none		none		20	
		hmetal		none		none		20	
		flesh		none		none		20	
		player		none		none		20	
		zip			none		none		10	
	end
end



ammo kz_Bite			
	bullet_mass	3
	max_age		1     
	arm_age		0      
	velocity	6		
	error		1
	drag		1
	recoil		0

	scorch_id	2
	scar_type	2

	flag instantkillzone	

	kztype rounds_kz_Standard
	kz_minradius 1.0	
	kz_maxradius 1.0	
	kz_damage 10		
	impact_damage 0		
    kz_physics 1		

    impact_AI_damage 0	
    kz_AI_damage    10

	effects_table
		move		none		none		0
		obj			none		none		200	
		dirt		none		none		20	
		grass		none		none		20	
		snow		none		none		20	
		cement		none		none		20	
		packeddirt	none		none 		20	
		water		none		none		20	
		railroad	none		none		20	
		mud			none		none		20	
		ice			none		none		20	
		quicksand	none		none		20	
		sand		none		none 		20	
		stone		none		none		20	
		wood		none		none		20	
		metal		none		none		20	
		glass		none		none		20	
		cloth		none		none		20	
		foliage		none		none		20	
		hmetal		none		none		20	
		flesh		none		none		20	
		player		none		none		20	
		zip			none		none		10	
	end
end


ammo AI_CLOSEKZ
	bullet_mass 1
	max_age 1     
	velocity 1		
	error 0
	drag  1

	impact_damage 100
    
	flag instantkillzone
	kztype rounds_kz_Slash
	kz_damage 13
	kz_minradius .5
	kz_maxradius .5

    impact_AI_damage 0	
    kz_AI_damage    13 

	effects_table
		move       none						none				0
		obj        none   imp_20mm_dirt		15
		dirt       Effect_PistolDirt		imp_20mm_dirt	15
		grass      Effect_PistolGrass		imp_bullet_grass 15
		snow       Effect_PistolSnow		imp_20mm_dirt	1
		cement     Effect_PistolStone		imp_20mm_dirt	15
		packeddirt Effect_PistolDirt		imp_20mm_dirt	15
		water      Effect_PistolWater		imp_20mm_water	5
		railroad   Effect_PistolMetal		imp_20mm_metal	15
		mud        Effect_PistolDirt		imp_bullet_mud   15
		ice        Effect_PistolSnow		imp_bullet_mud   15
		sand       Effect_PistolSand		IMP_BULLET_SAND	15
		quicksand  Effect_PistolSand		IMP_BULLET_SAND	15
		stone      Effect_PistolStone		imp_20mm_rock	15
		wood       Effect_PistolDirt		imp_20mm_wood	5
		metal      Effect_PistolMetal		imp_20mm_metal	15
		glass      Effect_PistolGlass		imp_glass			5
		cloth      Effect_PistolDirt		IMP_BULLET_CLOTH 3
		foliage    Effect_PistolGrass		imp_20mm_foliage 3
		hmetal     Effect_PistolMetal		imp_20mm_armor	15
		flesh      Effect_PistolBody		IMP_KNIFE_FLESH	3
		player		none					IMP_KNIFE_FLESH	10
		zip			none					wsh_shell_by	10
	end
end



