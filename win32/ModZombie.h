#pragma once

/// <summary>
/// Zombie damages plants every tick
/// </summary>
/// <param name="zombie"></param>
/// <param name="plant"></param>
/// <returns></returns>
ModObject* DamagePlant(ModObject* zombie, ModObject* plant);

/// <summary>
/// All zombies have health, damage, and speed
/// </summary>
/// <param name="plant"></param>
/// <returns></returns>
ModObject* CreateZombie(int zombie);
