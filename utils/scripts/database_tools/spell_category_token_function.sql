DELIMITER $$

DROP FUNCTION IF EXISTS `GetSpellCategoryToken`;

-- This function converts numeric spell category ids to a string label based on server code designations
--
-- example:
-- SELECT `id`, `name`, GetSpellCategoryToken(`spell_category`) FROM `spells_new` WHERE `id` IN ('39', '129', '3468');
CREATE FUNCTION `GetSpellCategoryToken` (`spell_category` INT(11)) RETURNS VARCHAR(256)
BEGIN
	DECLARE `token` VARCHAR(256) DEFAULT '';
	
	CASE `spell_category`
		WHEN '-99' THEN SET `token` = 'neg99#';
		WHEN '-1' THEN SET `token` = 'neg1#';
		WHEN '0' THEN SET `token` = CONCAT('#', `spell_category`);
		WHEN '1' THEN SET `token` = 'DD';
		WHEN '2' THEN SET `token` = 'DD_Undead';
		WHEN '3' THEN SET `token` = 'DD_Summoned';
		WHEN '4' THEN SET `token` = 'Lifetap_to_Self';
		WHEN '5' THEN SET `token` = 'DoT_Plant';
		WHEN '6' THEN SET `token` = 'DD_Body_Type';
		WHEN '7' THEN SET `token` = 'DoT';
		WHEN '8' THEN SET `token` = 'Divine_DoT';
		WHEN '9' THEN SET `token` = 'Lifetap_to_Self_2';
		WHEN '10' THEN SET `token` = 'AoE_DD';
		WHEN '11' THEN SET `token` = 'AoE_DD_Earth';
		WHEN '12' THEN SET `token` = 'AoE_DD_Nature';
		WHEN '13' THEN SET `token` = 'Bolt_Fire_Cold';
		WHEN '14' THEN SET `token` = 'Stun_Damage';
		WHEN '15' THEN SET `token` = 'Target_Stun';
		WHEN '16' THEN SET `token` = 'Group_Stun';
		WHEN '17' THEN SET `token` = 'Leech_to_Group';
		WHEN '18' THEN SET `token` = 'Siphon_Strength';
		WHEN '19' THEN SET `token` = 'Weapon_Proc';
		WHEN '20' THEN SET `token` = 'Target_Heal';
		WHEN '21' THEN SET `token` = 'Target_HoT';
		WHEN '22' THEN SET `token` = 'Group_Heal_Cure';
		WHEN '23' THEN SET `token` = 'Group_HoT';
		WHEN '24' THEN SET `token` = 'Target_Health_Regen';
		WHEN '25' THEN SET `token` = 'Group_Health_Regen';
		WHEN '26' THEN SET `token` = 'Pet_Heal';
		WHEN '27' THEN SET `token` = 'Resurrection';
		WHEN '28' THEN SET `token` = 'Dark_Empathy';
		WHEN '29' THEN SET `token` = 'Cure_Poison';
		WHEN '30' THEN SET `token` = 'Resolution';
		WHEN '32' THEN SET `token` = 'Blur';
		WHEN '34' THEN SET `token` = 'Hate_Buff';
		WHEN '35' THEN SET `token` = 'Attack_Speed_Buff';
		WHEN '36' THEN SET `token` = 'Pet_Combat_Buff';
		WHEN '37' THEN SET `token` = 'Attack_Speed_Buff_Song';
		WHEN '38' THEN SET `token` = 'Attack_Speed_Debuff';
		WHEN '39' THEN SET `token` = 'Attack_Speed_Debuff_2';
		WHEN '40' THEN SET `token` = 'Cannibalize';
		WHEN '41' THEN SET `token` = 'Target_Movement_Speed';
		WHEN '42' THEN SET `token` = 'Group_Movement_Speed';
		WHEN '43' THEN SET `token` = 'Wolf_Form';
		WHEN '44' THEN SET `token` = 'Elemental_Pet_Movement_Speed';
		WHEN '45' THEN SET `token` = 'Illusion';
		WHEN '46' THEN SET `token` = 'Dark_Pact';
		WHEN '47' THEN SET `token` = 'Form_of_the_Bear';
		WHEN '48' THEN SET `token` = 'Treeform';
		WHEN '49' THEN SET `token` = 'Dead_Man_Floating';
		WHEN '50' THEN SET `token` = 'Root';
		WHEN '51' THEN SET `token` = 'Summon_Pet';
		WHEN '52' THEN SET `token` = 'Summon_Corpse';
		WHEN '53' THEN SET `token` = 'Sense';
		WHEN '54' THEN SET `token` = 'Divine_Aura';
		WHEN '55' THEN SET `token` = 'Evacuate';
		WHEN '56' THEN SET `token` = 'Gate';
		WHEN '58' THEN SET `token` = 'Teleport_Bind';
		WHEN '59' THEN SET `token` = 'Shadow_Step';
		WHEN '60' THEN SET `token` = 'Enchant_Material';
		WHEN '61' THEN SET `token` = 'Summon_Common_Item';
		WHEN '62' THEN SET `token` = 'Fear';
		WHEN '63' THEN SET `token` = 'Fear_Animal';
		WHEN '64' THEN SET `token` = 'Fear_Undead';
		WHEN '65' THEN SET `token` = 'Damage_Shield';
		WHEN '66' THEN SET `token` = 'Resist_Buff_Song';
		WHEN '67' THEN SET `token` = CONCAT('#', `spell_category`);
		WHEN '68' THEN SET `token` = 'Damage_Shield_2';
		WHEN '69' THEN SET `token` = 'Resist_Redux';
		WHEN '70' THEN SET `token` = 'Resist_Buff';
		WHEN '71' THEN SET `token` = 'Warder';
		WHEN '72' THEN SET `token` = 'Familiar';
		WHEN '73' THEN SET `token` = 'Strength_Buff';
		WHEN '74' THEN SET `token` = 'Dexterity_Buff';
		WHEN '75' THEN SET `token` = 'Agility_Buff';
		WHEN '76' THEN SET `token` = 'Stamina_Buff';
		WHEN '77' THEN SET `token` = 'Intelligence_Wisdom_Buff';
		WHEN '78' THEN SET `token` = 'Charisma_Buff';
		WHEN '79' THEN SET `token` = 'Weaken';
		WHEN '80' THEN SET `token` = 'Invisibility_v_Undead';
		WHEN '81' THEN SET `token` = 'Invisibility_v_Animals';
		WHEN '82' THEN SET `token` = 'Invisibility';
		WHEN '83' THEN SET `token` = 'Damage_Absorbtion';
		WHEN '84' THEN SET `token` = 'Fizzle_Redux';
		WHEN '85' THEN SET `token` = 'Clarity';
		WHEN '86' THEN SET `token` = 'Gift_of_Magic';
		WHEN '87' THEN SET `token` = 'Mana_Drain';
		WHEN '88' THEN SET `token` = 'Mana_Subversion';
		WHEN '89' THEN SET `token` = 'Harvest_Mana';
		WHEN '90' THEN SET `token` = 'Hate_Redux';
		WHEN '91' THEN SET `token` = 'Increase_Aim';
		WHEN '92' THEN SET `token` = 'Combat_Buff';
		WHEN '93' THEN SET `token` = 'Bind_Sight';
		WHEN '94' THEN SET `token` = 'Enduring_Breath';
		WHEN '95' THEN SET `token` = 'Alliance';
		WHEN '96' THEN SET `token` = 'Charm';
		WHEN '97' THEN SET `token` = 'Strip_Enchantment';
		WHEN '98' THEN SET `token` = 'Lull';
		WHEN '99' THEN SET `token` = 'Mesmerize';
		WHEN '100' THEN SET `token` = 'Casting_Enhancement';
		WHEN '101' THEN SET `token` = 'Snare_Hamstring';
		WHEN '102' THEN SET `token` = 'Shackle';
		WHEN '105' THEN SET `token` = 'Feign_Death';
		WHEN '106' THEN SET `token` = 'Identify';
		WHEN '107' THEN SET `token` = 'Reclaim_Energy';
		WHEN '108' THEN SET `token` = 'Locate_Corpse';
		WHEN '109' THEN SET `token` = 'Call_of_the_Hero';
		WHEN '110' THEN SET `token` = 'Mana_Shield';
		WHEN '112' THEN SET `token` = 'Blind';
		WHEN '113' THEN SET `token` = 'Gravity_is_for_Suckers'; -- 'Levitation'
		WHEN '114' THEN SET `token` = 'Bard_Nerf';
		WHEN '115' THEN SET `token` = 'Divine_Intervention';
		WHEN '116' THEN SET `token` = 'Memory_Blur';
		WHEN '118' THEN SET `token` = 'Size_Change';
		WHEN '119' THEN SET `token` = 'Hate_Buff_2';
		WHEN '120' THEN SET `token` = CONCAT('#', `spell_category`);
		WHEN '121' THEN SET `token` = CONCAT('#', `spell_category`);
		WHEN '122' THEN SET `token` = CONCAT('#', `spell_category`);
		WHEN '125' THEN SET `token` = 'DD_Fire';
		WHEN '126' THEN SET `token` = 'DD_Cold';
		WHEN '127' THEN SET `token` = 'Bolt_Poison';
		WHEN '128' THEN SET `token` = 'Bolt_Disease';
		WHEN '129' THEN SET `token` = 'DoT_Fire';
		WHEN '130' THEN SET `token` = 'DoT_Cold';
		WHEN '131' THEN SET `token` = 'DoT_Poison';
		WHEN '132' THEN SET `token` = 'DoT_Disease';
		WHEN '133' THEN SET `token` = 'Destroy_Lock';
		WHEN '134' THEN SET `token` = 'Sense_Trap';
		WHEN '135' THEN SET `token` = 'Disarm_Trap';
		WHEN '136' THEN SET `token` = 'Destroy_Cursed_Lock';
		WHEN '137' THEN SET `token` = 'Sense_Cursed_Trap';
		WHEN '138' THEN SET `token` = 'Disarm_Cursed_Trap';
		WHEN '140' THEN SET `token` = 'Banish_Undead';
		WHEN '141' THEN SET `token` = 'Banish';
		WHEN '142' THEN SET `token` = 'AoE_DD_Fire_Column';
		WHEN '143' THEN SET `token` = 'AoE_DD_Cold_Column';
		WHEN '146' THEN SET `token` = 'AoE_DD_Fire';
		WHEN '147' THEN SET `token` = 'AoE_DD_Cold';
		WHEN '150' THEN SET `token` = 'AoE_DoT_Fire';
		WHEN '151' THEN SET `token` = 'AoE_DoT_Cold';
		WHEN '152' THEN SET `token` = 'AoE_DoT_Poison';
		WHEN '154' THEN SET `token` = 'AoE_Fear_Song';
		WHEN '155' THEN SET `token` = 'Target_Heal_2';
		WHEN '156' THEN SET `token` = 'Mana_to_HP';
		WHEN '157' THEN SET `token` = 'Symbiosis';
		WHEN '159' THEN SET `token` = 'Cure_Corruption';
		WHEN '160' THEN SET `token` = 'Remove_Curse';
		WHEN '161' THEN SET `token` = 'Cure';
		WHEN '162' THEN SET `token` = 'Cure_Blindness';
		WHEN '163' THEN SET `token` = 'Divine_Cure';
		WHEN '164' THEN SET `token` = CONCAT('#', `spell_category`);
		WHEN '165' THEN SET `token` = 'Magic_Combat_Buff';
		WHEN '166' THEN SET `token` = 'Nature_HP_Attack_Buff';
		WHEN '167' THEN SET `token` = 'Divine_HP_Buff';
		WHEN '168' THEN SET `token` = 'Divine_HP_AC_Buff';
		WHEN '169' THEN SET `token` = CONCAT('#', `spell_category`);
		WHEN '170' THEN SET `token` = 'Spell_Rune';
		WHEN '171' THEN SET `token` = 'Pet_Rune';
		WHEN '172' THEN SET `token` = 'Spell_Reflection';
		WHEN '173' THEN SET `token` = 'Damage_Shield_3';
		WHEN '174' THEN SET `token` = 'Vital_Regen';
		WHEN '175' THEN SET `token` = 'Aggro_Redux';
		WHEN '200' THEN SET `token` = 'Cantrips';
		WHEN '201' THEN SET `token` = CONCAT('#', `spell_category`);
		WHEN '202' THEN SET `token` = 'Combat_Buff_Song';
		WHEN '203' THEN SET `token` = 'Summon_Swarm';
		WHEN '204' THEN SET `token` = 'Summon_Air_Elemental';
		WHEN '205' THEN SET `token` = 'Summon_Water_Elemental';
		WHEN '206' THEN SET `token` = 'Summon_Fire_Elemental';
		WHEN '207' THEN SET `token` = 'Summon_Earth_Elemental';
		WHEN '208' THEN SET `token` = 'Monster_Summoning';
		WHEN '209' THEN SET `token` = 'Teleport_Antonica';
		WHEN '210' THEN SET `token` = 'Teleport_Odus';
		WHEN '211' THEN SET `token` = 'Teleport_Faydwer';
		WHEN '212' THEN SET `token` = 'Teleport_Combine';
		WHEN '213' THEN SET `token` = 'Teleport_Velious';
		WHEN '214' THEN SET `token` = 'Teleport_Luclin';
		WHEN '215' THEN SET `token` = 'Teleport_Planes';
		WHEN '216' THEN SET `token` = 'Teleport_Gates';
		WHEN '217' THEN SET `token` = 'Summon_Weapon';
		WHEN '218' THEN SET `token` = 'Summon_Jewelry';
		WHEN '219' THEN SET `token` = 'Summon_Sustenance';
		WHEN '220' THEN SET `token` = 'Summon_Armor';
		WHEN '999' THEN SET `token` = CONCAT('#', `spell_category`);
		ELSE SET `token` = 'unk';
	END CASE;
	
	SET `token` = CONCAT(`token`, '(', `spell_category`, ')');
	
	RETURN `token`;
END$$

DELIMITER ;
