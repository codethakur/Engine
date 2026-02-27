{
    "name": "MyScene",
    "objects": [
        {
            "name": "object_0"
            "position": {"x": 2, "y": 2, "z":2 },
            "rotation": {"x": 0, "y": 0, "z": 1, "w", 1},
            "scale":    {"x": 1, "y": 1, "z": 1}
            "components":[
                {
                    "type:" "MeshComponent",
                    "material": "materials/brick.mat",
                    "mesh": {
                        "type": "box",
                        "x": 2,
                        "y": 1,
                        "z": 5
                    }
                }
            ]
        }
    ]
}