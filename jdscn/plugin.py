bl_info = {
        "name":         "jdscn file export",
        "author":       "Loek Le Blansch",
        "blender":      (2, 80, 0),
        "version":      (0, 0, 1),
        "location":     "File > Export",
        "description":  "Export jdscn data format",
        "category":     "Import-Export"
        }

import bpy, bpy_extras, re, json, math, jsonschema, bmesh

class ExportJDSCN(bpy.types.Operator, bpy_extras.io_utils.ExportHelper):
    bl_idname = "export.jdscn"
    bl_label = "Export jdscn"

    filename_ext = ".jdscn"

    def execute(self, context):
        out = {
                "meta": {
                    "version": "1.5",
                    "generator": "Blender jdscn export plugin"
                    },
                "lights": [],
                "objects": []
                }

        for current_object in context.scene.objects:
            current_object_out = {
                    "position": list(current_object.location),
                    "orientation": list(current_object.rotation_euler),
                    "meta": {
                        "name": current_object.name_full
                        },
                    }
            if(current_object.type == "CAMERA"):
                current_object_out["focalLength"] = bpy.data.cameras[0].lens # FIXME: search for scene camera instead of picking the first/only camera
                if(not hasattr(out, "camera")):
                    out["camera"] = current_object_out
            elif(current_object.type == "LIGHT"):
                current_object_out["power"] = current_object.data.energy
                current_object_out["type"] = current_object.data.type.lower()
                current_object_out["radius"] = current_object.data.shadow_soft_size
                current_object_out["color"] = list(map(lambda c: int(c * 255), list(current_object.data.color)))
                current_object_out["cone"] = 0 if current_object.data.type != "SPOT" else current_object.data.spot_size
                out["lights"].append(current_object_out)
            elif(current_object.type == "MESH"):
                current_object_out["scale"] = list(current_object.scale)
                current_object_out["vertices"] = []

                bmesh_object = bmesh.new()
                bmesh_object.from_mesh(current_object.data)
                bmesh_object_triangulated = bmesh.ops.triangulate(bmesh_object,
                        faces=bmesh_object.faces,
                        quad_method="BEAUTY",
                        ngon_method="BEAUTY")

                vertices = list(map(lambda v: list(v.co), list(current_object.to_mesh().vertices)))
                for face in bmesh_object_triangulated["faces"]:
                    verts = list(map(lambda v: v.index, list(face.verts)))
                    resolvedFace = list(map(lambda i: vertices[i], verts))
                    current_object_out["vertices"].append(resolvedFace)

                materials = current_object.data.materials
                nodes = materials[0].node_tree.nodes if len(materials) > 0 else None

                if nodes != None and "Principled BSDF" in materials[0].node_tree.nodes:
                    inputs = nodes["Principled BSDF"].inputs
                    color = list(inputs["Base Color"].default_value)
                    color.pop()
                    current_object_out["material"] = dict()
                    current_object_out["material"]["color"] = list(map(lambda c: int(c * 255), color))
                    current_object_out["material"]["roughness"] = inputs["Roughness"].default_value
                    current_object_out["material"]["metallic"] = inputs["Metallic"].default_value
                    current_object_out["material"]["transparency"] = inputs["Alpha"].default_value
                    current_object_out["material"]["meta"] = {"name": current_object.data.materials[0].name_full}
                else:
                    current_object_out["material"] = {
                            "color": [255, 255, 255],
                            "roughness": 0.5,
                            "metallic": 0.0,
                            "transparency": 0.5,
                            "meta": {"name": "unsupported material"}
                            }

                if nodes != None and "Image Texture" in nodes:
                    image = nodes["Image Texture"].image
                    current_object_out["texture"] = {}
                    current_object_out["texture"]["path"] = image.filepath
                    current_object_out["texture"]["name"] = image.name_full
                    current_object_out["texture"]["uv"] = [] # TODO: uv map of triangulated mesh

                # bmesh_object_triangulated['face_map']
                # https://stackoverflow.com/questions/13327379/how-to-export-per-vertex-uv-coordinates-in-blender-export-script
                # https://docs.blender.org/api/current/bmesh.html

                out["objects"].append(current_object_out)

        # write file
        file = open(self.filepath, "w")
        file.write(re.sub(r"\[(\n\ +)([\d.,\-]+)(\n\ +)([\d.,\-]+)(\n\ +)([\d.,\-]+)(\n\s+)\]", "[\g<2> \g<4> \g<6>]", json.dumps(out, indent=4)))
        file.close()

        return {"FINISHED"}

def menu_export(self, content):
    self.layout.operator(ExportJDSCN.bl_idname, text="jdscn (.jdscn)")

def register():
    bpy.utils.register_class(ExportJDSCN)
    bpy.types.TOPBAR_MT_file_export.append(menu_export)

def unregister():
    bpy.utils.unregister_class(ExportJDSCN)
    bpy.types.TOPBAR_MT_file_export.remove(menu_export)

if __name__ == "__main__":
    register()

