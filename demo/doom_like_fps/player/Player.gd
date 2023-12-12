class_name DoomLikeFPSExamplePlayer extends CharacterBody3D


const SPEED = 5.0
const JUMP_VELOCITY = 4.5

# Get the gravity from the project settings to be synced with RigidBody nodes.
var gravity: float = ProjectSettings.get_setting("physics/3d/default_gravity")

@export_category("Player Setup")
@export var mouse_sensitivity: float = 0.004


@onready var active_weapon_0: EquippedItem3D = $CameraNeck/Camera3D/LeftHand
@onready var active_weapon_1: EquippedItem3D = $CameraNeck/Camera3D/RightHand
@onready var camera_neck: Node3D = $CameraNeck
@onready var camera_shake: CameraShake = $CameraShake
@onready var equipment: Equipment = $Equipment
@onready var gameplay_attribute_map: GameplayAttributeMap = $GameplayAttributeMap
@onready var hud = $Hud


var equipped_weapon: DoomLikeFPSWeaponItem
var shotgun: DoomLikeFPSShotgun
var smg: DoomLikeFPSSMG


func _ready() -> void:
	# note: you can (and you should) add slots and accepted items using the editor's ui 
	# I am doing programmatically because I prefer coding (it helps me iterate on this exampels faster when I change a resource's code)
	shotgun = DoomLikeFPSShotgun.new()
	smg = DoomLikeFPSSMG.new()
	
	equipment.slots.append(EquipmentSlot.new([shotgun, smg]))
	equipment._ready()

	equipment.tag_added.connect(func (tag, _tags):
		hud.equipment_tag_added(tag)
	)
	
	equipment.equipped.connect(func (weapon, _slot):
		# Since we can have only one equipped item in this scenario, we save
		# the reference to it into the Player object.
		# On other scenarioes, a good approach would consist in cycling all the Equipment.equipped_items and activate one by one
		equipped_weapon = weapon
		hud.handle_equipped(weapon)
	)

	equipment.item_activated.connect(func (weapon, _slot):
		camera_shake.shake(weapon.recoil, 0.2, 10)	
	)

	gameplay_attribute_map.attribute_changed.connect(hud.handle_attribute_changed)

	hud.handle_attribute_changed(gameplay_attribute_map.get_attribute_by_name("health"))
	hud.handle_attribute_changed(gameplay_attribute_map.get_attribute_by_name("armor"))


func _physics_process(delta: float) -> void:
	# Add the gravity.
	if not is_on_floor():
		velocity.y -= gravity * delta

	# Handle Jump.
	if Input.is_action_just_pressed("fps_jump") and is_on_floor():
		velocity.y = JUMP_VELOCITY

	# Get the input direction and handle the movement/deceleration.
	# As good practice, you should replace UI actions with custom gameplay actions.
	var input_dir := Input.get_vector("fps_strafe_left", "fps_strafe_right", "fps_move_forward", "fps_move_backward")
	var direction := (transform.basis * Vector3(input_dir.x, 0, input_dir.y)).normalized()
	if direction:
		velocity.x = direction.x * SPEED
		velocity.z = direction.z * SPEED
	else:
		velocity.x = move_toward(velocity.x, 0, SPEED)
		velocity.z = move_toward(velocity.z, 0, SPEED)

	if Input.is_action_pressed("fps_shoot") and equipped_weapon:
		equipment.activate(equipped_weapon)

	move_and_slide()


func _input(event: InputEvent):
	if event is InputEventMouseMotion:
		var y = event.relative.x * mouse_sensitivity
		var x = event.relative.y * mouse_sensitivity
		rotate_y(-y)
		camera_neck.rotate_x(x)
		camera_neck.rotation.x = clamp(camera_neck.rotation.x, -1.2, 1.2)
	
	if event.is_action_pressed("fps_weapon_1"):
		if not equipment.is_equipped(shotgun):
			equipment.equip(shotgun)

	if event.is_action_pressed("fps_weapon_2"):
		if not equipment.is_equipped(smg):
			equipment.equip(smg)
