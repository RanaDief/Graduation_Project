"""One-time editor setup. Creates missing assets only; preserves existing work."""
import unreal as u
import json
from pathlib import Path
root='/Game/WordsWeNeverSaid'
a=u.get_editor_subsystem(u.EditorAssetSubsystem)
l=u.get_editor_subsystem(u.LevelEditorSubsystem)
s=u.get_editor_subsystem(u.EditorActorSubsystem)
t=u.AssetToolsHelpers.get_asset_tools()
u.AssetRegistryHelpers.get_asset_registry().wait_for_completion()
def bp(name,parent):
 path=root+'/Core/'+name
 if a.does_asset_exist(path): return u.load_asset(path)
 f=u.BlueprintFactory(); f.set_editor_property('parent_class',parent)
 obj=t.create_asset(name,root+'/Core',u.Blueprint,f)
 assert obj and a.save_loaded_asset(obj)
 return obj
bp('BP_GameInstance',u.GameInstance)
bp('BP_GameMode',u.GameModeBase)
path=root+'/Maps/Development/L_Development'
if not a.does_asset_exist(path):
 assert l.new_level(path,is_partitioned_world=False)
 floor=s.spawn_actor_from_class(u.StaticMeshActor,u.Vector(0,0,-25))
 floor.set_actor_label('DevelopmentFloor')
 floor.static_mesh_component.set_static_mesh(u.load_asset('/Engine/BasicShapes/Cube'))
 floor.set_actor_scale3d(u.Vector(20,20,0.5))
 light=s.spawn_actor_from_class(u.DirectionalLight,u.Vector(0,0,500),u.Rotator(pitch=-45,yaw=-30))
 light.set_actor_label('DevelopmentLight')
 s.spawn_actor_from_class(u.PlayerStart,u.Vector(0,0,100))
 u.get_editor_subsystem(u.UnrealEditorSubsystem).set_level_viewport_camera_info(u.Vector(-1000,-1000,900),u.Rotator(pitch=-30,yaw=45))
 assert l.save_current_level()
assert l.load_level(path)
assets=list(a.list_assets(root,recursive=True,include_folder=False))
report={'saved_assets':assets,'map_loaded':True,'actor_count':len(s.get_all_level_actors()),'custom_gameplay':False}
Path(u.Paths.project_dir(),'Build','workspace_check.json').write_text(json.dumps(report,indent=2))
u.log('WORKSPACE_READY '+json.dumps(report))
