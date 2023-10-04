package org.example;

import net.querz.mca.Chunk;
import net.querz.mca.MCAFile;
import net.querz.mca.MCAUtil;

import java.io.IOException;

public class Main {
    private static final int REGION_SIZE = 32;

    public static void main(String[] args) throws IOException {
        MCAFile file = MCAUtil.read("C:\\Users\\jesse\\Documents\\projects\\NBT\\src\\main\\resources\\r.0.0.mca");

        for (int x = 0; x < REGION_SIZE; x++)
        {
            for (int z = 0; z < REGION_SIZE; z++)
            {
                var chunk = file.getChunk(x, z);
                if (chunk != null) {
                    var tileEntities = chunk.getTileEntities();
                    for (var tileEntity : tileEntities) {
                        var id = tileEntity.getString("id");

                        // The tile entity that will be read also contains the absolute coordinates of the tile entity,
                        // think this is faster
                        var absX = tileEntity.getInt("x");
                        var absZ = tileEntity.getInt("z");
                        System.out.println("[" + x + ", " + z + "](" + absX + ", " + absZ + "): " + id);

                        if (id.equals("minecraft:mob_spawner"))
                        {
                            var spawnData = tileEntity.getCompoundTag("SpawnData");
                            var entityID = spawnData.getString("id");
                            System.out.println("TYPE: " + entityID);
                        }
                    }
                }
            }
        }
    }
}
